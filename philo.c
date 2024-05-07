#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

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


int main(int    ac, char    *av[],  char    *env[])
{
    pthread_mutex_t forks;
    if (ac < 5 || ac > 6)
        (write(2, "wrong number of args\n", 22), exit(1));
    int n_philos;
    int time_die;
    int time_eat;
    int time_sleep;
    int n_times_philo_eat;
    int n_forks;

    n_philos = ft_atoi(av[1]);    
    time_die = ft_atoi(av[2]);    
    time_eat = ft_atoi(av[3]);    
    time_sleep = ft_atoi(av[4]);
    if (ac == 6)
        n_times_philo_eat = ft_atoi(av[5]);
    else
        n_times_philo_eat = -1;
    
    return 0;
}