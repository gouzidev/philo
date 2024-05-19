#include "philo.h"

long    get_done(t_data *data)
{
    LOCK(&data->done_mutex);
    if (data->done)
    {
        UNLOCK(&data->done_mutex);
        return (1);
    }
    UNLOCK(&data->done_mutex);
    return (0);
}
long get_ready_threads(t_data *data)
{
    long ready_threads;
    LOCK(&data->ready_threads_mutex);
    ready_threads = data->ready_threads;
    UNLOCK(&data->ready_threads_mutex);
    return (ready_threads);
}

long    set_ready_threads(t_data *data, long new_ready_threads)
{
    LOCK(&data->ready_threads_mutex);
    data->ready_threads = new_ready_threads;
    UNLOCK(&data->ready_threads_mutex);
    return (new_ready_threads);
}

long    get_last_ate(t_philo *philo)
{
    long last_ate;
    LOCK(&philo->last_ate_mutex);
    last_ate = philo->last_ate;
    UNLOCK(&philo->last_ate_mutex);
    return (last_ate);
}

