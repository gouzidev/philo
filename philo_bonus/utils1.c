/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:17:01 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 03:50:27 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	millisecons_passed(void)
{
	struct timeval	now;
	long			time_mille;

	gettimeofday(&now, NULL);
	time_mille = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time_mille);
}

long	get_timestamp(t_data *data)
{
	return (millisecons_passed() - data->init_time);
}

int freee(t_data *data)
{
	free(data->philos);
	free(data->pids);
	free(data);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return -1;
	return (res * sign);
}

void	safe_print(t_data *data, int id, char *msg)
{
	long	curr_timestamp;

	curr_timestamp = get_timestamp(data);
	sem_wait(data->print_sem);
	printf(msg, curr_timestamp, id + 1);
	sem_post(data->print_sem);
}
