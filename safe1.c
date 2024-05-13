#include "philo.h"

void set_done(t_data *data, long new_done)
{
    LOCK(&data->done_mutex);
    data->done = new_done;
    UNLOCK(&data->done_mutex);
}

void set_started(t_data *data, long new_started)
{
    LOCK(&data->started_mutex);
    data->started = new_started;
    UNLOCK(&data->started_mutex);
}

void set_time(t_data *data, long new_time)
{
    LOCK(&data->time_mutex);
    data->time = new_time;
    UNLOCK(&data->time_mutex);
}

void set_ready_threads_count(t_data *data, long new_ready_threads_count)
{
    LOCK(&data->ready_threads_count_mutex);
    data->ready_threads_count = new_ready_threads_count;
    UNLOCK(&data->ready_threads_count_mutex);
}

void set_eat_count(t_philo *philo, long new_eat_count)
{
    LOCK(&philo->eat_count_mutex);
    philo->eat_count = new_eat_count;
    UNLOCK(&philo->eat_count_mutex);
}