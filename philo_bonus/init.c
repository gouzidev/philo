/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:42 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 03:47:11 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*parse(int ac, char *av[])
{
	t_data	*data;
	int	i;

	if (ac != 5 && ac != 6)
		(printf("bad number of args\n"), exit(1));
	data = malloc(sizeof(t_data));
    data->nthreads = ft_atoi(av[1], 'p');
    data->time_to_die = ft_atoi(av[2], 't');
    data->time_to_eat = ft_atoi(av[3], 't');
    data->time_to_sleep = ft_atoi(av[4], 't');
	if (ac == 6)
		data->n_eat_times = ft_atoi(av[5], 'n');
	else
		data->n_eat_times = -1;
	printf("data->nthreads -> %d\n", data->nthreads);
	printf("data->time_to_die -> %ld\n", data->time_to_die);
	printf("data->time_to_eat -> %ld\n", data->time_to_eat);
	printf("data->time_to_sleep -> %ld\n", data->time_to_sleep);
    data->philos = malloc(sizeof(t_philo) * data->nthreads);
	data->pids = malloc(sizeof(pid_t) * data->nthreads);
	i = -1;
	while (++i < data->nthreads)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
	}
	return (data);
}

int	verify(t_data *data, int ac)
{
    if (data->nthreads > 200 || data->nthreads < 1)
        return 0;
    if (data->n_eat_times < 1 && ac == 6)
        return 0;
    if (data->time_to_die < 60)
        return 0;
    if (data->time_to_eat < 60)
        return 0;
    if (data->time_to_sleep < 60)
        return 0;
    return 1;
    
}
