#include "philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]

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

void safe_print(char *msg, t_data *data, int philo_id)
{
    pthread_mutex_lock(&data->printf_mutex);
    printf(msg, data->time, philo_id);
    pthread_mutex_unlock(&data->printf_mutex);
}

void ph_eat(t_data *data, int philo_id)
{
    safe_print("%ld %d is eating\n", data, philo_id);
    usleep(data->time_to_eat * 1000);
    data->time +=data->time_to_eat;
}

void ph_sleep(t_data *data, int philo_id)
{
    safe_print("%ld %d is sleeping\n", data, philo_id);
    usleep(data->time_to_sleep * 1000);
    data->time +=data->time_to_sleep;
}

int is_odd(int n)
{
    return n % 2;
}

void init_fork_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
        i++;
    }
}

void dest_fork_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_mutex_destroy(&data->forks[i].fork_mutex);
        i++;
    }
}
void LOCK(pthread_mutex_t *thread)
{
    pthread_mutex_lock(thread);
}
void UNLOCK(pthread_mutex_t *thread)
{
    pthread_mutex_unlock(thread);
}
t_data *init_data (int ac, char *av[])
{
    t_data *data;
    int i;

    if (ac < 5)
    {
        printf("bad number of args\n");
        exit(1);
    }
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
    data->philos = malloc(sizeof(t_philo) * data->nthreads);
    data->forks = malloc(sizeof(t_fork) * data->nthreads);
    data->time = 0;
    i = -1;
    while (++i < data->nthreads)
    {
        data->philos[i].data = data;
        data->philos[i].philo_id = i;
        data->philos[i].is_dead = 0;
        data->philos[i].left_hand = NULL;
        data->philos[i].right_hand = NULL;
        data->forks[i].fork_n = i;
        data->forks[i].busy = 0;
    }
    return data;    
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