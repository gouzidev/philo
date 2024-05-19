#include "philo.h"

void	precise_usleep(t_data *data, long time)
{
   // long	expected;

    (void)data;
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
}

int ft_think(t_data *data, int id)
{
    long curr_timestamp;

    if (get_done(data))
        return 0;
    curr_timestamp = get_timestamp(data);
    if (get_done(data))
        return 0;
    precise_usleep(NULL, 1);
    if (get_done(data))
        return 0;
    LOCK(&data->printf_mutex);
    printf("%ld %d is thinking\n", curr_timestamp, id + 1);
    UNLOCK(&data->printf_mutex);
    return 1;
}

int ft_eat(t_data *data, t_philo *philo)
{
    if (get_done(data))
        return (0);
    LOCK(philo->right_hand);
    if (get_done(data))
    {
        UNLOCK(philo->right_hand);
        return (0);
    }
    LOCK(&data->printf_mutex);
    printf("%ld %d has taken a fork\n", get_timestamp(data), philo->id + 1);
    UNLOCK(&data->printf_mutex);
    LOCK(philo->left_hand);
    if (get_done(data))
    {
        UNLOCK(philo->left_hand);
        UNLOCK(philo->right_hand);
        return (0);
    }
    LOCK(&data->printf_mutex);
    printf("%ld %d is eating\n", get_timestamp(data), philo->id + 1);
    UNLOCK(&data->printf_mutex);
    set_last_ate(philo, millisecons_passed());
    precise_usleep(NULL, data->time_to_eat);
    UNLOCK(philo->left_hand);
    UNLOCK(philo->right_hand);
    return (1);
}

int ft_sleep(t_data *data, int id)
{
    if (get_done(data))
        return 0;
    safe_print(data, id + 1, "%ld %d is sleeping\n");
    if (get_done(data))
        return 0;
    precise_usleep(NULL, data->time_to_sleep);
    if (get_done(data))
        return 0;
    return 1;
}
