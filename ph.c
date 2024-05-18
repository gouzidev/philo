#include "philo.h"

void	precise_usleep(t_data *data, long time)
{
    long	expected;

    (void)data;
	expected = get_curr_time() + time;
	while (get_curr_time() < expected)
	{
	}
}



int ft_think(t_data *data, int id)
{
    long curr_timestamp;

    if (get_done(data))
        return 0;
    curr_timestamp = get_timestamp(data);
    if (get_done(data))
        return 0;
    usleep(1);
    LOCK(&data->printf_mutex);
    printf("%ld %d is thinking\n", curr_timestamp, id + 1);
    UNLOCK(&data->printf_mutex);
    return 1;
}

void pickup_forks(t_philo *philo, pthread_mutex_t *hands[2])
{
    if (philo->id % 2 == 0)
    {
        hands[0] = philo->right_hand;
        hands[1] = philo->left_hand;
    }
    else
    {
        hands[0] = philo->left_hand;
        hands[1] = philo->right_hand;
    }
}

int ft_eat(t_data *data, t_philo *philo)
{
    pthread_mutex_t *hands[2];

    pickup_forks(philo, hands);
    if (get_done(data))
        return (0);
    LOCK(hands[0]);
    safe_print(data, philo->id + 1, "%ld %d has taken a fork\n");
    if (get_done(data))
    {
        UNLOCK(hands[0]);
        return (0);
    }
    LOCK(hands[1]);
    safe_print(data, philo->id + 1, "%ld %d has taken a fork\n");
    if (get_done(data))
    {
        UNLOCK(hands[1]);
        UNLOCK(hands[0]);
        return (0);
    }
    safe_print(data, philo->id + 1, "%ld %d is eating\n");
    set_last_ate(philo, get_curr_time());
    usleep(data->time_to_eat * 1000);
    UNLOCK(hands[1]);
    UNLOCK(hands[0]);

    return (1);

}


int ft_sleep(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    safe_print(data, id + 1, "%ld %d is sleeping\n");
    usleep(data->time_to_sleep * 1000);
    if (get_done(data))
        return 0;
    return 1;
}

void ft_die(t_data *data, int id)
{
    LOCK(&data->printf_mutex);
    printf("%ld %d died\n", get_timestamp(data), id + 1);
    UNLOCK(&data->printf_mutex);
    set_done(data, 1);
}
int gonna_die(t_data *data, int ph_id)
{
    long last_ate;
    long now = get_curr_time();
    last_ate = get_last_ate(&data->philos[ph_id]);
    return (now - last_ate > data->time_to_die);
}
