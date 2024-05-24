/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:51 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 01:50:07 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	set_ready_threads(t_data *data, long new_ready_threads)
{
	lock(&data->ready_threads_mutex);
	data->ready_threads = new_ready_threads;
	unlock(&data->ready_threads_mutex);
	return (new_ready_threads);
}

void	set_done(t_data *data, long new_done)
{
	lock(&data->done_mutex);
	data->done = new_done;
	unlock(&data->done_mutex);
}

void	set_last_ate(t_philo *philo, long new_last_ate)
{
	lock(&philo->last_ate_mutex);
	philo->last_ate = new_last_ate;
	unlock(&philo->last_ate_mutex);
}

void	set_eat_count(t_philo *philo, long new_eat_count)
{
	lock(&philo->eat_count_mutex);
	philo->eat_count = new_eat_count;
	unlock(&philo->eat_count_mutex);
}