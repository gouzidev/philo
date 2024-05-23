/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:53 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 00:48:35 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_semaphores(t_data *data)
{
	sem_unlink("/print");
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	data->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0644,
			data->nthreads);
}

void	close_semaphores(t_data *data)
{
	(void)data;
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_close(data->print_sem);
	sem_close(data->forks_sem);
}

long	get_running(t_data *data)
{
	long	running;

	sem_wait(data->print_sem);
	running = data->running;
	sem_post(data->print_sem);
	return (running);
}

void	set_running(t_data *data, long new_running)
{
	sem_wait(data->print_sem);
	data->running = new_running;
	sem_post(data->print_sem);
}

void	precise_usleep(long time)
{
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
}
