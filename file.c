#include "philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]

void init_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        pthread_mutex_init(&data->philos[i].last_ate_mutex, NULL);
        i++;
    }
    pthread_mutex_init(&data->printf_mutex, NULL);
    pthread_mutex_init(&data->done_mutex, NULL);
    set_done(data, 0);
}

void dest_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].last_ate_mutex);
        i++;
    }
    pthread_mutex_destroy(&data->printf_mutex);
    pthread_mutex_destroy(&data->done_mutex);
}

t_data *parse(int ac, char *av[])
{
    t_data *data;

    if (ac < 5)
        (printf("bad number of args\n"), exit(1));
    data = malloc(sizeof(t_data));
    if (ac >= 5 && ac <= 6)
    {
        data->nthreads = ft_atoi(av[1]);
        data->time_to_die = ft_atoi(av[2]);
        data->time_to_eat = ft_atoi(av[3]);
        data->time_to_sleep = ft_atoi(av[4]);
    }
    if (ac == 6)
        data->n_eat_times = ft_atoi(av[4]);
    else
        data->n_eat_times = -1;
    return data;
}
void init_data (t_data *data)
{
    int i;

    data->philos = malloc(sizeof(t_philo) * data->nthreads);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->nthreads);
    i = -1;
    while (++i < data->nthreads)
    {
        data->philos[i].data = data;
        data->philos[i].id = i;
        data->philos[i].right_hand = NULL;
        data->philos[i].left_hand = NULL;
    }
    assign_forks(data);
}

void create_threads(t_data *data, void *(*routine)(void *))
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
        i++;
    }
}

void join_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}

void assign_forks(t_data *data)
{
    int i;
    int nphilos;

    nphilos = data->nthreads;
    i = -1;
    if (nphilos == 1)
    {
        data->philos[0].right_hand = &data->forks[0];
        data->philos[0].left_hand = NULL;
        return ;
    }
    while (++i < data->nthreads)
    {
        data->philos[i].right_hand = &data->forks[i];
        data->philos[i].left_hand = &data->forks[i + 1 % nphilos];
    }
}
#include "philo.h"

void	precise_usleep(t_data *data, long time)
{
   // long	expected;

    (void)data;
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
}

int ft_think(t_data *data, int id)
{
    long curr_timestamp;

    if (get_done(data))
        return 0;
    curr_timestamp = get_timestamp(data);
    if (get_done(data))
        return 0;
    precise_usleep(NULL, 1);
    if (get_done(data))
        return 0;
    LOCK(&data->printf_mutex);
    printf("%ld %d is thinking\n", curr_timestamp, id + 1);
    UNLOCK(&data->printf_mutex);
    return 1;
}

int ft_eat(t_data *data, t_philo *philo)
{
    if (get_done(data))
        return (0);
    LOCK(philo->right_hand);
    if (get_done(data))
    {
        UNLOCK(philo->right_hand);
        return (0);
    }
    LOCK(&data->printf_mutex);
    printf("%ld %d has taken a right fork\n", get_timestamp(data), philo->id + 1);
    UNLOCK(&data->printf_mutex);
    LOCK(philo->left_hand);
    if (get_done(data))
    {
        UNLOCK(philo->left_hand);
        UNLOCK(philo->right_hand);
        return (0);
    }
    LOCK(&data->printf_mutex);
    printf("%ld %d has taken a left  fork\n", get_timestamp(data), philo->id + 1);
    printf("%ld %d is eating\n", get_timestamp(data), philo->id + 1);
    UNLOCK(&data->printf_mutex);
    set_last_ate(philo, millisecons_passed());
    
    precise_usleep(NULL, data->time_to_eat);
    UNLOCK(philo->left_hand);
    UNLOCK(philo->right_hand);
    return (1);
}

int ft_sleep(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    safe_print(data, id + 1, "%ld %d is sleeping\n");
    if (get_done(data))
        return 0;
    precise_usleep(NULL, data->time_to_sleep);
    if (get_done(data))
        return 0;
    return 1;
}
#include "philo.h"

int will_die(t_philo *philo)
{
    long time_to_die;

    time_to_die = philo->data->time_to_die;
    return (millisecons_passed() - get_last_ate(philo) > time_to_die);
}
void release_forks(t_philo *philo)
{
    if (philo->left_hand != NULL)
    {
        UNLOCK(philo->left_hand);
    }
    if (philo->right_hand != NULL)
    {
        UNLOCK(philo->right_hand);
    }
}

void observer(t_data *data)
{
    int i;
    precise_usleep(data, 1);
    while (1)
    {
        i = 0;
        while (i < data->nthreads)
        {
            if (will_die(&data->philos[i]))
            {
                release_forks(&data->philos[i]);
                LOCK(&data->done_mutex);
                LOCK(&data->printf_mutex);
                printf("%ld %d died\n", get_timestamp(data), data->philos[i].id + 1);
                data->done = 1;
                UNLOCK(&data->printf_mutex);
                UNLOCK(&data->done_mutex);
                return ;
            }
            i++;
        }
    }
        printf("done %ld\n", get_done(data));
}

void *routine(void *arg)
{
    int ate;
    int slept;
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;
    set_last_ate(philo, millisecons_passed());
    if (philo->id % 2)
        precise_usleep(NULL, 60);
    while (1)
    {
        ate = ft_eat(data, philo);
        if (!ate)
            return NULL;
        if (get_done(data))
            return NULL;
        slept = ft_sleep(data, philo->id);
        if (!slept)
            return NULL;
        if (get_done(data))
            return NULL;
        ft_think(data, philo->id);
            if (get_done(data))
                return NULL;
    }
    return NULL;
}

int main(int ac, char *av[])
{
    t_data *data;

    data = parse(ac, av);
    init_data(data);
    init_mutexes(data);
    set_done(data, 0);
    data->init_time = millisecons_passed();
    create_threads(data, routine);
    observer(data);
    join_threads(data);
    dest_mutexes(data);
}#include "philo.h"

void set_done(t_data *data, long new_done)
{
    LOCK(&data->done_mutex);
    data->done = new_done;
    UNLOCK(&data->done_mutex);
}

void set_last_ate(t_philo *philo, long new_last_ate)
{
    LOCK(&philo->last_ate_mutex);
    philo->last_ate = new_last_ate;
    UNLOCK(&philo->last_ate_mutex);
}
#include "philo.h"

long    get_done(t_data *data)
{
    long done;
    LOCK(&data->done_mutex);
    done = data->done;
    UNLOCK(&data->done_mutex);
    return (done);
}

long    get_last_ate(t_philo *philo)
{
    long last_ate;
    LOCK(&philo->last_ate_mutex);
    last_ate = philo->last_ate;
    UNLOCK(&philo->last_ate_mutex);
    return (last_ate);
}

#include "philo.h"

void LOCK(pthread_mutex_t *thread)
{
    pthread_mutex_lock(thread);
}

void UNLOCK(pthread_mutex_t *thread)
{
    pthread_mutex_unlock(thread);
}

long millisecons_passed()
{
    struct timeval now;
    long time_mille;
    gettimeofday(&now, NULL);
    time_mille = (now.tv_sec * 1000) + (now.tv_usec / 1000);
    return time_mille;
}

long get_timestamp(t_data *data)
{
    return millisecons_passed() - data->init_time;
}#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void safe_print(t_data *data, int id, char *msg)
{
	long curr_timestamp;

	if (get_done(data)) return;
	
    LOCK(&data->printf_mutex);
    curr_timestamp = get_timestamp(data);
    printf(msg, curr_timestamp, id);
    UNLOCK(&data->printf_mutex);
}
