#include "philo.h"

long    get_done(t_data *data)
{
    long done;
    LOCK(&data->done_mutex);
    done = data->done;
    UNLOCK(&data->done_mutex);
    return (done);
}

long    get_started(t_data *data)
{
    long started;
    LOCK(&data->started_mutex);
    started = data->started;
    UNLOCK(&data->started_mutex);
    return (started);
}

long    get_time(t_data *data)
{
    long time;
    LOCK(&data->time_mutex);
    time = data->time;
    UNLOCK(&data->time_mutex);
    return (time);
}

long    get_ready_threads_count(t_data *data)
{
    long ready_threads_count;
    LOCK(&data->ready_threads_count_mutex);
    ready_threads_count = data->ready_threads_count;
    UNLOCK(&data->ready_threads_count_mutex);
    return (ready_threads_count);
}

long    get_eat_count(t_philo *philo)
{
    long eat_count;
    LOCK(&philo->eat_count_mutex);
    eat_count = philo->eat_count;
    UNLOCK(&philo->eat_count_mutex);
    return (eat_count);
}

long    get_last_ate(t_philo *philo)
{
    long last_ate;
    LOCK(&philo->last_ate_mutex);
    last_ate = philo->last_ate;
    UNLOCK(&philo->last_ate_mutex);
    return (last_ate);
}
