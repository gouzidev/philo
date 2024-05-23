/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:54 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 01:50:01 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_running(t_data *data)
{
	long running;
	sem_wait(data->print_sem);
	running = data->running;
	sem_post(data->print_sem);
	return running;
}

void	set_running(t_data *data, long new_running)
{
	sem_wait(data->print_sem);
	data->running = new_running;
	sem_post(data->print_sem);
}

struct timeval	get_last_ate(t_philo *philo)
{
	struct timeval	last_ate;

	sem_wait(philo->data->print_sem);
	last_ate = philo->last_ate;
	sem_post(philo->data->print_sem);
	return (last_ate);
}
