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

void	set_last_ate(t_philo *philo, struct timeval new_last_ate)
{
	sem_wait(philo->data->print_sem);
	philo->last_ate = new_last_ate;
	sem_post(philo->data->print_sem);
}
