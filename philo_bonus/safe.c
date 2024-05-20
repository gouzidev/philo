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

void	set_alive(t_philo *philo, long new_alive)
{
	sem_wait(philo->alive_sem);
	philo->alive = new_alive;
	sem_post(philo->alive_sem);
}

void	set_last_ate(t_philo *philo, long new_last_ate)
{
	sem_wait(philo->last_ate_sem);
	philo->last_ate = new_last_ate;
	sem_post(philo->last_ate_sem);
}

void set_eat_count(t_philo *philo, long new_eat_count)
{
    sem_wait(philo->eat_count_sem);
    philo->eat_count = new_eat_count;
    sem_post(philo->eat_count_sem);
}