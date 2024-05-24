/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:54 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 09:59:31 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_done(t_data *data)
{
	lock(&data->done_mutex);
	if (data->done)
	{
		unlock(&data->done_mutex);
		return (1);
	}
	unlock(&data->done_mutex);
	return (0);
}

long	get_ready_threads(t_data *data)
{
	long	ready_threads;

	lock(&data->ready_threads_mutex);
	ready_threads = data->ready_threads;
	unlock(&data->ready_threads_mutex);
	return (ready_threads);
}

long	get_last_ate(t_philo *philo)
{
	long	last_ate;

	lock(&philo->last_ate_mutex);
	last_ate = philo->last_ate;
	unlock(&philo->last_ate_mutex);
	return (last_ate);
}

long	get_eat_count(t_philo *philo)
{
	long	eat_count;

	lock(&philo->eat_count_mutex);
	eat_count = philo->eat_count;
	unlock(&philo->eat_count_mutex);
	return (eat_count);
}
