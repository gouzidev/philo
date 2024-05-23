/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:53 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 02:58:25 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_semaphores(t_data *data)
{
	sem_unlink("/print");
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	data->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nthreads);
}

void close_semaphores(t_data *data)
{
	(void) data;
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_close(data->print_sem);
	sem_close(data->forks_sem);
}
