/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 00:46:38 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 09:47:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*parse(int ac, char *av[])
{
	t_data	*data;
	int		i;

	if (ac != 5 && ac != 6)
		(printf("bad number of args\n"), exit(1));
	data = malloc(sizeof(t_data));
	if (!data)
		(printf("malloc\n"), exit(1));
	get_args(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->nthreads);
	if (!data->philos)
		(free(data), printf("malloc failed\n"), exit(1));
	data->pids = malloc(sizeof(pid_t) * data->nthreads);
	if (!data)
		(free(data), free(data->philos), printf("malloc failed\n"), exit(1));
	i = -1;
	while (++i < data->nthreads)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
	}
	return (data);
}

void	get_args(t_data *data, int ac, char *av[])
{
	data->nthreads = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->n_eat_times = -1;
	if (ac == 6)
		data->n_eat_times = ft_atoi(av[5]);
}

int	verify(t_data *data, int ac)
{
	if (!data)
		return (0);
	if (data->nthreads > 200 || data->nthreads < 1)
		return (0);
	if (data->n_eat_times < 1 && ac == 6)
		return (0);
	if (data->time_to_die < 60)
		return (0);
	if (data->time_to_eat < 60)
		return (0);
	if (data->time_to_sleep < 60)
		return (0);
	return (1);
}
