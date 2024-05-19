#include "philo.h"

long    get_done(t_data *data)
{
    long done;
    LOCK(&data->done_mutex);
    done = data->done;
    UNLOCK(&data->done_mutex);
    return (done);
}

long    get_last_ate(t_philo *philo)
{
    long last_ate;
    LOCK(&philo->last_ate_mutex);
    last_ate = philo->last_ate;
    UNLOCK(&philo->last_ate_mutex);
    return (last_ate);
}

