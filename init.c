#include "philo.h"

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
t_data *init_data (int nthreads)
{
    struct timeval tv;
    t_data *data;
    int i;

    gettimeofday(&tv, NULL);
    data = malloc(sizeof(t_data));
    data->philos = malloc(sizeof(t_philo) * nthreads);
    data->forks = malloc(sizeof(t_fork) * nthreads);
    data->time = tv.tv_usec;
    data->nthreads = nthreads;
    i = 0;
    while (i < nthreads)
    {
        data->philos[i].philo_id = i;
        data->philos[i].is_dead = 0;
        data->philos[i].time_die = 800;
        data->philos[i].time_eat = 100;
        data->philos[i].time_think = 100;
        data->philos[i].data = data;
        data->forks[i].fork_n = i;
        data->forks[i].busy = 0;
        i++;
    }
    return data;    
}