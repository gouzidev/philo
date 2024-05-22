#include "philo.h"

t_data	*parse(int ac, char *av[])
{
	t_data	*data;
	int	i;

	if (ac != 5 && ac != 6)
		(printf("bad number of args\n"), exit(1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
    data->nthreads = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	data->n_eat_times = -1;
	if (ac == 6)
		data->n_eat_times = ft_atoi(av[5]);
	data->philos = malloc(sizeof(t_philo) * data->nthreads);
	data->pids = malloc(sizeof(pid_t) * data->nthreads);
	i = -1;
	while (++i < data->nthreads)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
	}
	return (data);
}

int	verify(t_data *data, int ac)
{
    if (data->nthreads > 200 || data->nthreads < 1)
        return 0;
    if (data->n_eat_times < 1 && ac == 6)
        return 0;
    if (data->time_to_die < 60)
        return 0;
    if (data->time_to_eat < 60)
        return 0;
    if (data->time_to_sleep < 60)
        return 0;
    return 1;
    
}
#include "philo.h"


void kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	sem_post(data->print_sem);
}

void	*observer(void *arg)
{
	t_data *data;
	t_philo *philo;

	philo = (t_philo *)arg;
	data = philo->data;

	while (1)
	{
		if (get_last_ate(philo) != 0 && will_die(philo))
		{
			sem_wait(data->print_sem);
			printf("%ld %d died\n", get_timestamp(data), philo->id);
			freee(data);
			exit(1);
		}
	}
	return NULL;
}

int ft_eat(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0);
	sem_wait(data->forks_sem);
	safe_print(data, philo->id, "%ld %d has taken a left  fork\n");
	if (!get_running(data))
		return (sem_post(data->forks_sem), 0) ;
	sem_wait(data->forks_sem);
	safe_print(data, philo->id, "%ld %d has taken a right fork\n");
	if (!get_running(data))
		return (sem_post(data->forks_sem), sem_post(data->forks_sem), 0);
	safe_print(data, philo->id, "%ld %d is eating\n");
	set_last_ate(philo, millisecons_passed());
	set_eat_count(philo, get_eat_count(philo) + 1);
	precise_usleep(data->time_to_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	if (data->n_eat_times == get_eat_count(philo))
		exit(0);
	return (1);
}

int ft_sleep(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0) ;
	safe_print(data, philo->id, "%ld %d is sleeping\n");
	if (!get_running(data))
		return (0) ;
	precise_usleep(data->time_to_sleep);
	return (1);
}

int ft_think(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0);
	safe_print(data, philo->id, "%ld %d is thinking\n");
	if (!get_running(data))
		return (0);
	precise_usleep(1);
	return (1);
}

void process(t_philo *philo) // routine
{
	t_data *data;
	int good;
	pthread_t thread;

	data = philo->data;
	if (philo->id % 2 == 0)
	 	precise_usleep(1);
	set_last_ate(philo, millisecons_passed());
	set_eat_count(philo, 0);
	set_running(data, 1);
	pthread_create(&thread, NULL, observer, philo);
	while(1)
	{
		good = ft_eat(data, philo);
		if (!good)
			break;
		good = ft_sleep(data, philo);
		if (!good)
			break;
		good = ft_think(data, philo);
		if (!good)
			break;
	}
	pthread_join(thread, NULL);
}

int	main(int ac, char *av[])
{
	t_data	*data;
	int	good;
	int i;
	int id;

	data = parse(ac, av);
	good = verify(data, ac);
	if (!good)
		return (printf("bad args\n"), free(data->philos), free(data), 1);
	init_semaphores(data);
	data->init_time = millisecons_passed();
	set_running(data, 1);
	i = -1;
	while (++i < data->nthreads)
	{
		id = fork();
		data->pids[i] = id;
		if (id == 0)
			process(&data->philos[i]);
		else if (id == -1)
			return (freee(data));
	}
	waiter(data);
	close_semaphores(data);
	return freee(data);
}
#include "philo.h"

void	set_last_ate(t_philo *philo, long new_last_ate)
{
	sem_wait(philo->data->print_sem);
	philo->last_ate = new_last_ate;
	sem_post(philo->data->print_sem);
}

void set_eat_count(t_philo *philo, long new_eat_count)
{
    sem_wait(philo->data->print_sem);
    philo->eat_count = new_eat_count;
    sem_post(philo->data->print_sem);
#include "philo.h"

long	get_running(t_data *data)
{
	long running;
	sem_wait(data->print_sem);
	running = data->running;
	sem_post(data->print_sem);
	return running;
}

void	set_running(t_data *data, long new_running)
{
	sem_wait(data->print_sem);
	data->running = new_running;
	sem_post(data->print_sem);
}

long	get_last_ate(t_philo *philo)
{
	long	last_ate;

	sem_wait(philo->data->print_sem);
	last_ate = philo->last_ate;
	sem_post(philo->data->print_sem);
	return (last_ate);
}

long	get_eat_count(t_philo *philo)
{
	long	eat_count;

	sem_wait(philo->data->print_sem);
	eat_count = philo->eat_count;
	sem_post(philo->data->print_sem);
	return (eat_count);
#include "philo.h"

int	will_die(t_philo *philo)
{
	int		should_die;
	long	time_since_ate;
	long	time_to_die;

	time_to_die = philo->data->time_to_die;
	time_since_ate = (millisecons_passed() - get_last_ate(philo));
	should_die = time_since_ate > time_to_die;
	return (should_die);
}

void waiter(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while(i < data->nthreads)
	{
		waitpid(-1, &status, 0);
		if (status >> 8 == 1)
			kill_all(data);
		i++;
	}
}

void init_semaphores(t_data *data)
{
	sem_unlink("/print");
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	data->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nthreads);
}

void close_semaphores(t_data *data)
{
	(void) data;
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_close(data->print_sem);
	sem_close(data->forks_sem);
}

void	precise_usleep(long time)
{
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
#include "philo.h"

long	millisecons_passed(void)
{
	struct timeval	now;
	long			time_mille;

	gettimeofday(&now, NULL);
	time_mille = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time_mille);
}

long	get_timestamp(t_data *data)
{
	return (millisecons_passed() - data->init_time);
}

int freee(t_data *data)
{
	free(data->philos);
	free(data->pids);
	free(data);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return -1;
	return (res * sign);
}

void	safe_print(t_data *data, int id, char *msg)
{
	long	curr_timestamp;

	curr_timestamp = get_timestamp(data);
	sem_wait(data->print_sem);
	printf(msg, curr_timestamp, id + 1);
	sem_post(data->print_sem);
}
