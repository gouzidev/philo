/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:46:43 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 00:49:30 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
}

int	main(int ac, char *av[])
{
	t_data	*data;
	int		good;
	int		i;
	int		id;

	data = parse(ac, av);
	good = verify(data, ac);
	if (!good)
		return (printf("bad args\n"), free(data->philos), free(data), 1);
	init_semaphores(data);
	data->init_time = millisecons_passed();
	data->meals_eaten = 0;
	set_running(data, 1);
	i = -1;
	while (++i < data->nthreads)
	{
		id = fork();
		data->pids[i] = id;
		if (id == 0)
			process(&data->philos[i]);
		else if (id == -1)
			return (freee(data));
	}
	waiter(data);
	return (close_semaphores(data), freee(data));
}

void	waiter(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		waitpid(-1, &status, 0);
		if (status >> 8 == 1)
		{
			if (WIFEXITED(status) == 1)
				break ;
		}
		i++;
	}
	kill_all(data);
	sem_post(data->print_sem);
}
