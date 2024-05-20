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

void	lock(pthread_mutex_t *thread)
{
	pthread_mutex_lock(thread);
}

void	unlock(pthread_mutex_t *thread)
{
	pthread_mutex_unlock(thread);
}

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
	free(data->forks);
	free(data->philos);
	free(data->pids);
	free(data);
	return (0);
}
