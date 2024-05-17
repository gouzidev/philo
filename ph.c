#include "philo.h"

int ft_think(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    long curr_timestamp;

    curr_timestamp = get_timestamp(data);
    if (get_done(data))
        return 0;
    LOCK(&data->printf_mutex);
    printf("%ld %d is thinking\n", curr_timestamp, id);
    UNLOCK(&data->printf_mutex);
    return 1;
}

int ft_eat(t_data *data, t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        if (get_done(data))
            return (0);
        LOCK(philo->right_hand);
        safe_print(data, philo->id, "%ld %d has taken right fork\n");
        if (get_done(data))
        {
            UNLOCK(philo->right_hand);
            return (0);
        }
        LOCK(philo->left_hand);
        safe_print(data, philo->id, "%ld %d has taken left  fork\n");
        if (get_done(data))
        {
            UNLOCK(philo->left_hand);
            UNLOCK(philo->right_hand);
            return (0);
        }
        safe_print(data, philo->id, "%ld %d is eating\n");
        safe_usleep(data, data->time_to_eat * 1000);
        UNLOCK(philo->left_hand);
        UNLOCK(philo->right_hand);
    }
    else
    {
        if (get_done(data))
            return (0);
        LOCK(philo->left_hand);
        safe_print(data, philo->id, "%ld %d has taken left  fork\n");
        if (get_done(data))
        {
            UNLOCK(philo->left_hand);
            return (0);
        }
        LOCK(philo->right_hand);
        safe_print(data, philo->id, "%ld %d has taken right fork\n");
        if (get_done(data))
        {
            UNLOCK(philo->right_hand);
            UNLOCK(philo->left_hand);
            return (0);
        }
        safe_print(data, philo->id, "%ld %d is eating\n");
        safe_usleep(data, data->time_to_eat * 1000);
        UNLOCK(philo->right_hand);
        UNLOCK(philo->left_hand);
    }
    set_last_ate(philo, get_curr_time());
    return (1);

}


int ft_sleep(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    safe_print(data, id, "%ld %d is sleeping\n");
    safe_usleep(data, data->time_to_sleep * 1000);
    if (get_done(data))
        return 0;
    return 1;
}

void ft_die(t_data *data, int id)
{
    LOCK(&data->printf_mutex);
    printf("%ld %d died\n", get_timestamp(data), id);
    set_done(data, 1);
    UNLOCK(&data->printf_mutex);
}
int gonna_die(t_data *data, int ph_id)
{
    long last_ate;
    long now = get_curr_time();
    last_ate = get_last_ate(&data->philos[ph_id]);
    return (now - last_ate > data->time_to_die);
}
