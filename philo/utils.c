/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:53 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 10:00:24 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return (res * sign);
}

void	safe_print(t_data *data, int id, char *msg)
{
	long	curr_timestamp;

	if (get_done(data))
		return ;
	if (data->nthreads == get_eat_count(&data->philos[id - 1]))
		return ;
	lock(&data->printf_mutex);
	curr_timestamp = get_timestamp(data);
	printf(msg, curr_timestamp, id);
	unlock(&data->printf_mutex);
}

int	will_die(t_philo *philo)
{
	int		should_die;
	long	time_since_ate;
	long	time_to_die;

	time_to_die = philo->data->time_to_die;
	time_since_ate = (millisecons_passed() - get_last_ate(philo));
	should_die = time_since_ate > time_to_die;
	return (should_die);
}
