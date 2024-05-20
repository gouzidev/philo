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

long	get_alive(t_philo *philo)
{
	long alive;
	sem_wait(philo->alive_sem);
	alive = philo->alive;
	sem_post(philo->alive_sem);
	return alive;
}

long	get_last_ate(t_philo *philo)
{
	long	last_ate;

	sem_wait(philo->last_ate_sem);
	last_ate = philo->last_ate;
	sem_post(philo->last_ate_sem);
	return (last_ate);
}

long	get_eat_count(t_philo *philo)
{
	long	eat_count;

	sem_wait(philo->eat_count_sem);
	eat_count = philo->eat_count;
	sem_post(philo->eat_count_sem);
	return (eat_count);
}