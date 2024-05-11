#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void safe_print(char *msg, t_data *data, int philo_id)
{
    long curr_timestamp;

    curr_timestamp = get_timestamp(data);
    pthread_mutex_lock(&data->printf_mutex);
    printf(msg, curr_timestamp, philo_id);
    pthread_mutex_unlock(&data->printf_mutex);
}

void ph_eat(t_data *data, int philo_id)
{
    safe_print("%ld %d is eating\n", data, philo_id);
    usleep(data->time_to_eat * 1000);
    data->philos[philo_id].time_last_meal = get_curr_time();

}

void ph_sleep(t_data *data, int philo_id)
{
    struct timeval tv;
    safe_print("%ld %d is sleeping\n", data, philo_id);
    usleep(data->time_to_sleep * 1000);
    gettimeofday(&tv, NULL);
}

