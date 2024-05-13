#include "philo.h"

void ph_think(t_data *data, int id)
{
    if (get_done(data))
        return;
    long curr_timestamp;

    curr_timestamp = get_timestamp(data);
    LOCK(&data->printf_mutex);
    printf("%ld %d is thinking\n", curr_timestamp, id);
    UNLOCK(&data->printf_mutex);
}
void ph_pair_eat(t_data *data, int id)
{
    LOCK(&data->forks[id]);
    safe_print(data, id, "%ld %d has taken a right fork\n");
    LOCK(&data->forks[(id + 1) % data->nthreads]);
    safe_print(data, id, "%ld %d has taken a left  fork\n");
    safe_print(data, id, "%ld %d is eating\n");
    usleep(data->time_to_eat * 1000);
    UNLOCK(&data->forks[(id + 1) % data->nthreads]);
    UNLOCK(&data->forks[id]);
    data->philos[id].time_last_meal = get_curr_time();
}

void ph_impair_eat(t_data *data, int id)
{
    LOCK(&data->forks[(id + 1) % data->nthreads]);
    safe_print(data, id, "%ld %d has taken a left  fork\n");
    LOCK(&data->forks[id]);
    safe_print(data, id, "%ld %d has taken a right fork\n");
    safe_print(data, id, "%ld %d is eating\n");
    usleep(data->time_to_eat * 1000);
    UNLOCK(&data->forks[(id + 1) % data->nthreads]); 
    UNLOCK(&data->forks[id]);
    data->philos[id].time_last_meal = get_curr_time();
}

void decide_first_fork(t_data *data, int id)
{
    if (id % 2 == 0) /* pair */
        ph_pair_eat(data, id);
    else
        ph_impair_eat(data, id);
}

void ph_eat(t_data *data, int id)
{
    if (get_done(data))
        return;
    decide_first_fork(data, id);
}

void ph_sleep(t_data *data, int id)
{
	long curr_timestamp;

    if (get_done(data))
        return;

    curr_timestamp = get_timestamp(data);
    LOCK(&data->printf_mutex);
    printf("%ld %d is sleeping\n", curr_timestamp, id);
    UNLOCK(&data->printf_mutex);
    usleep(data->time_to_sleep * 1000);
}

void ph_die(t_data *data, int id)
{
    LOCK(&data->printf_mutex);
    printf("%ld %d died\n\n", get_timestamp(data), id);
    set_done(data, 1);
    UNLOCK(&data->printf_mutex);
}
int gonna_die(t_data *data, int ph_id)
{
    t_philo *philo;

    philo = &data->philos[ph_id];
    long now = get_curr_time();
    LOCK(&data->printf_mutex);
    printf("checking \n");
    UNLOCK(&data->printf_mutex);
    return (now - philo->time_last_meal > data->time_to_eat);
}
