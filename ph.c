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
int ph_pair_eat(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    LOCK(&data->forks[id]);
    if (get_done(data)) {
        UNLOCK(&data->forks[id]);
        return -1;
    }
    safe_print(data, id, "%ld %d has taken a right fork\n");

    if (data->nthreads > 1)
    {
        LOCK(&data->forks[(id + 1) % data->nthreads]);
        if (get_done(data)) {
            UNLOCK(&data->forks[(id + 1) % data->nthreads]);
            UNLOCK(&data->forks[id]);
            return -1;
        }
        safe_print(data, id, "%ld %d has taken a left  fork\n");
        safe_print(data, id, "%ld %d is eating\n");
        usleep(data->time_to_eat * 1000);
        set_last_ate(&data->philos[id], get_curr_time());
        UNLOCK(&data->forks[(id + 1) % data->nthreads]);
    }
    UNLOCK(&data->forks[id]);
    return 0;
}

int ph_impair_eat(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    LOCK(&data->forks[(id + 1) % data->nthreads]);
    if (get_done(data)) {
        UNLOCK(&data->forks[(id + 1) % data->nthreads]);
        return -1;
    }
    safe_print(data, id, "%ld %d has taken a left  fork\n");
    LOCK(&data->forks[id]);
    if (get_done(data)) {
        UNLOCK(&data->forks[id]);
        UNLOCK(&data->forks[(id + 1) % data->nthreads]);
        return -1;
    }
    safe_print(data, id, "%ld %d has taken a right fork\n");
    safe_print(data, id, "%ld %d is eating\n");
    usleep(data->time_to_eat * 1000);
    set_last_ate(&data->philos[id], get_curr_time());
    UNLOCK(&data->forks[(id + 1) % data->nthreads]); 
    UNLOCK(&data->forks[id]);
    return 0;
}

int decide_first_fork(t_data *data, int id)
{
    int sig;

    if (id % 2 == 0) /* pair */
        sig = ph_pair_eat(data, id);
    else
        sig = ph_impair_eat(data, id);
    return sig;
}

void ph_eat(t_data *data, int id)
{
    if (get_done(data))
        return;
    if (decide_first_fork(data, id) != -1 && !get_done(data))
        ph_sleep(data, id);
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
    long last_ate;
    long now = get_curr_time();
    last_ate = get_last_ate(&data->philos[ph_id]);
    UNLOCK(&data->printf_mutex);
    return (now - last_ate > data->time_to_eat);
}
