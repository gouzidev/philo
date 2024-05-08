#include "philo.h"

void    *routine(void   *arg)
{
	t_philo *philo;
    philo = (t_philo *)arg;
	pthread_mutex_lock(philo->forks_mutex);

    printf("%ld %d has taken a fork\n",philo->tv->tv_usec, philo->number);

	pthread_mutex_unlock(philo->forks_mutex);
}

t_data   *init_data(int   n_threads)
{
    t_data *data;
    int i;

	data = malloc(sizeof(t_data));
	struct timeval *tv;
	tv = malloc(sizeof(struct timeval));
	gettimeofday(tv, NULL);
	pthread_mutex_t	*forks_mutex;
    data->philos = malloc(sizeof(t_philo) * n_threads);
	forks_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(forks_mutex, NULL);
	i = 0;
	while (i < n_threads)
    {
        data->philos[i].number = i;
		data->philos[i].forks_mutex = forks_mutex;
		data->philos[i].tv = tv;
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
        i++;
    }

    i = 0;
    while (i < n_threads)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
	pthread_mutex_destroy(forks_mutex);
    return data;   
}

int main(int    ac, char    *av[],  char    *env[])
{
    t_data *data;
    data = init_data(4);
    return 0;
}