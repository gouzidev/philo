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

void safe_print(t_data *data, int id, char *msg)
{
	long curr_timestamp;

	if (get_done(data)) return;
	
    LOCK(&data->printf_mutex);
    curr_timestamp = get_timestamp(data);
    printf(msg, curr_timestamp, id);
    UNLOCK(&data->printf_mutex);
}
