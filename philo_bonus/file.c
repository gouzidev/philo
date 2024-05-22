
#include "philo.h"

t_data	*parse(int ac, char *av[])
{
	t_data	*data;
	int	i;

	if (ac != 5 && ac != 6)
		(printf("bad number of args\n"), exit(1));
	data = malloc(sizeof(t_data));
    data->nthreads = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_eat_times = ft_atoi(av[5]);
	else
		data->n_eat_times = -1;
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

void	precise_usleep(long time)
{
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
}


void kill_all(t_data *data, int philo_id)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		if (i != philo_id)
		{
			safe_print(data, i, "%ld %d died\n");
			kill(data->pids[i], SIGKILL);
		}
		i++;
	}
	kill(data->pids[philo_id], SIGKILL);
}

void	*observer(void *arg)
{
	t_data *data;
	t_philo *philo;
	int	i;

	philo = (t_philo *)arg;
	data = philo->data;
	sem_wait(data->start_sem);
	while (1)
	{
		i = 0;
		while (i < data->nthreads)
		{
			if (will_die(&data->philos[i]))
			{
				kill_all(data, i);
				safe_print(data, i, "%ld %d died\n");
				set_running(data, 0);
				return NULL;
			}
			i++;
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

	data = philo->data;

	if (philo->id % 2 == 0)
	 	precise_usleep(1);
	pthread_t thread;
	pthread_create(&thread, NULL, observer, philo);
	
	set_last_ate(philo, millisecons_passed());
	sem_post(data->start_sem);
	while(1)
	{
		int good;
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
	init_semaphores(data);
	i = 0;

	if (!good)
		return (free(data->philos), free(data), 1);
	i = 0;
	data->init_time = millisecons_passed();
	set_running(data, 1);
	while (i < data->nthreads)
	{
		id = fork();
		if (id == 0)
			process(&data->philos[i]);
		else if (id == -1)
			return (freee(data));
		else
			data->pids[i] = id;
		i++;
	}
	waiter(data);
	close_semaphores(data);
	return freee(data);
}



long	get_alive(t_philo *philo)
{
	long alive;
	sem_wait(philo->data->print_sem);
	alive = philo->alive;
	sem_post(philo->data->print_sem);
	return alive;
}

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
}


void	set_alive(t_philo *philo, long new_alive)
{
	sem_wait(philo->data->print_sem);
	philo->alive = new_alive;
	sem_post(philo->data->print_sem);
}

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
}

int	len(char const *s1)
{
	int	l;

	l = 0;
	while (s1[l])
		l++;
	return (l);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	output = (char *)malloc((len(s1) + len(s2) + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (i < len(s1))
	{
		output[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len(s2))
		output[i++] = s2[j++];
	output[i] = '\0';
	return (output);
}

int	count_digits(int n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*buff;
	int		digit_len;
	int		i;

	digit_len = count_digits(n);
	buff = (char *)malloc((digit_len + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL); // Return NULL if memory allocation fails
	
	buff[digit_len] = '\0';
	i = digit_len - 1;
	while (n > 0)
	{
		buff[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (buff);
}

char	*join_str_num(char	*str,	int	num)
{
	char	*n;
	char	*res;

	n = ft_itoa(num);
	res = ft_strjoin(str, n);
	free(n);
	return (res);
}



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

void	safe_print(t_data *data, int id, char *msg)
{
	long	curr_timestamp;

	curr_timestamp = get_timestamp(data);
	sem_wait(data->print_sem);
	printf(msg, curr_timestamp, id + 1);
	sem_post(data->print_sem);
}

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
		if (status == 0)
		{
			if (status >> 8 == 0)
				return ;
		}
		i++;
	}
}

void init_semaphores(t_data *data)
{
	sem_unlink("/print");
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	data->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nthreads);
	sem_unlink("/start");
	data->start_sem = sem_open("/start", O_CREAT | O_EXCL, 0644, 0);
}

void close_semaphores(t_data *data)
{
	(void) data;
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/start");
}