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
        pthread_mutex_init(&data->philos[i].eat_count_mutex, NULL);
        i++;
    }
    pthread_mutex_init(&data->printf_mutex, NULL);
    pthread_mutex_init(&data->started_mutex, NULL);
    pthread_mutex_init(&data->done_mutex, NULL);
    pthread_mutex_init(&data->time_mutex, NULL);
    pthread_mutex_init(&data->ready_threads_count_mutex, NULL);
}

void dest_mutexes(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].last_ate_mutex);
        pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
        i++;
    }
    pthread_mutex_destroy(&data->printf_mutex);
    pthread_mutex_destroy(&data->started_mutex);
    pthread_mutex_destroy(&data->done_mutex);
    pthread_mutex_destroy(&data->time_mutex);
    pthread_mutex_destroy(&data->ready_threads_count_mutex);
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
    data->init_time = get_curr_time();
    set_ready_threads_count(data, 0);
    i = -1;
    while (++i < data->nthreads)
    {
        data->philos[i].data = data;
        data->philos[i].id = i;
        data->philos[i].gonna_die = 0;
        data->philos[i].left_hand = NULL;
        data->philos[i].right_hand = NULL;
        data->philos[i].init_time = get_curr_time();
        data->philos[i].last_ate = get_curr_time();
    }
    assign_forks(data);
    data->init_time = get_curr_time();
}

void create_threads(t_data *data, void *(*routine)(void *))
{
    int i;

    i = 0;
    while (i < data->nthreads)
    {
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
        set_ready_threads_count(data, get_ready_threads_count(data) + 1);
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
    while (++i < data->nthreads)
    {
        data->philos[i].right_hand = &data->forks[i];
        data->philos[i].left_hand = &data->forks[i + 1 % nphilos];
    }
}