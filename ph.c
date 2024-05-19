#include "philo.h"

int ft_think(t_data *data, int id);

void	precise_usleep(t_data *data, long time)
{
   // long	expected;

    (void)data;
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
}

int ft_eat(t_data *data, t_philo *philo)
{
    int id = philo->id;

    if (get_done(data))
        return 0;
    LOCK(data->philos[id].right_hand);
    safe_print(data, id + 1, "%ld %d has taken a right fork\n");
    if (get_done(data))
    {
        UNLOCK(data->philos[id].right_hand);
        return 0;
    }
    LOCK(data->philos[id].left_hand);
    safe_print(data, id + 1, "%ld %d has taken a left fork\n");
    if (get_done(data))
    {
        UNLOCK(data->philos[id].right_hand);
        UNLOCK(data->philos[id].left_hand);
        return 0;
    }
    set_last_ate(&data->philos[id], millisecons_passed());
    safe_print(data, id + 1, "%ld %d is eating\n");
    precise_usleep(NULL, data->time_to_eat);
    if (get_done(data))
    {
        UNLOCK(data->philos[id].right_hand);
        UNLOCK(data->philos[id].left_hand);
        return 0;
    }
    UNLOCK(data->philos[id].right_hand);
    UNLOCK(data->philos[id].left_hand);
    return 1;
}

// int ft_eat(t_data *data, t_philo *philo)
// {
//     if (get_done(data))
//         return (0);
//     LOCK(philo->right_hand);
//     if (get_done(data))
//     {
//         LOCK(&data->printf_mutex);
//         printf("unlocking right hand for %d\n", philo->id + 1);
//         UNLOCK(&data->printf_mutex);
//         UNLOCK(philo->right_hand);
//         return (0);
//     }
//     LOCK(&data->printf_mutex);
//     printf("%ld %d has taken a right fork\n", get_timestamp(data), philo->id + 1);
//     UNLOCK(&data->printf_mutex);
//     LOCK(philo->left_hand);
//     if (get_done(data))
//     {
//         LOCK(&data->printf_mutex);
//         printf("unlocking left hand for %d\n", philo->id + 1);
//         UNLOCK(&data->printf_mutex);
//         UNLOCK(philo->left_hand);
//         LOCK(&data->printf_mutex);
//         printf("unlocking right hand for %d\n", philo->id + 1);
//         UNLOCK(&data->printf_mutex);
//         UNLOCK(philo->right_hand);
//         return (0);
//     }
//     LOCK(&data->printf_mutex);
//     printf("%ld %d has taken a left fork\n", get_timestamp(data), philo->id + 1);
//     printf("%ld %d is eating\n", get_timestamp(data), philo->id + 1);
//     UNLOCK(&data->printf_mutex);
//     set_last_ate(philo, millisecons_passed());
    
//     precise_usleep(NULL, data->time_to_eat);
//     UNLOCK(philo->left_hand);
//     LOCK(&data->printf_mutex);
//     printf("%ld %d has dropped left fork\n", get_timestamp(data), philo->id + 1);
//     UNLOCK(&data->printf_mutex);
//     LOCK(&data->printf_mutex);
//     printf("%ld %d has dropped right fork\n", get_timestamp(data), philo->id + 1);
//     UNLOCK(&data->printf_mutex);
//     UNLOCK(philo->right_hand);
//     return (1);
// }

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