/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:15:55 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 03:52:08 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void process(t_data *data)
{
	
}

int	main(int ac, char *av[])
{
	t_data	*data;
	sem_t *print_sem;
	sem_t *philos_sem;
	int	good;
	int i;
	int id;

	data = parse(ac, av);
	good = verify(data, ac);
	if (!good)
		return (free(data->forks), free(data->philos), free(data), 1);
	print_sem = sem_open("/print", O_RDONLY | O_CREAT, 0644, 1);
	philos_sem = sem_open("/philos", O_RDONLY | O_CREAT, 0644, data->nthreads);

	i = 0;
	while (i < data->nthreads)
	{
		id = fork();
		if (id == 0)
		{
			
		}
		else if (id == -1)
			return (freee(data));
			
	}
	sem_close(philos_sem);
	sem_close(print_sem);

	return freee(data);
}
