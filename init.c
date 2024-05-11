#include "philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]


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

void check_death(t_philo *philo)
{
    long curr_time;
    long time_since_last_meal;

    pthread_mutex_lock(&philo->data->printf_mutex);
    curr_time = get_curr_time();
    time_since_last_meal = curr_time - philo->time_last_meal;
    if (time_since_last_meal > philo->data->time_to_die)
    {
        printf("%ld %d died\n", time_since_last_meal, philo->philo_id);
        exit(0);
    }
    pthread_mutex_unlock(&philo->data->printf_mutex);

}
t_data *init_data (int ac, char *av[])
{
    t_data *data;
    struct timeval *tv;
    int i;

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
    tv = malloc(sizeof(struct timeval));
    gettimeofday(tv, NULL);
    data->philos = malloc(sizeof(t_philo) * data->nthreads);
    data->forks = malloc(sizeof(t_fork) * data->nthreads);
    data->init_time = get_curr_time();
    i = -1;
    while (++i < data->nthreads)
    {
        data->philos[i].data = data;
        data->philos[i].philo_id = i;
        data->philos[i].is_dead = 0;
        data->philos[i].left_hand = NULL;
        data->philos[i].right_hand = NULL;
        data->philos[i].init_time = get_curr_time();
        data->philos[i].time_last_meal = get_curr_time();
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