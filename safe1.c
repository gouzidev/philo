#include "philo.h"

void set_done(t_data *data, long new_done)
{
    LOCK(&data->done_mutex);
    data->done = new_done;
    UNLOCK(&data->done_mutex);
}

void set_last_ate(t_philo *philo, long new_last_ate)
{
    LOCK(&philo->last_ate_mutex);
    philo->last_ate = new_last_ate;
    UNLOCK(&philo->last_ate_mutex);
}
