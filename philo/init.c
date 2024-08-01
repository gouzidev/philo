/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:42 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 10:21:24 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].last_ate_mutex, NULL);
		pthread_mutex_init(&data->philos[i].eat_count_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->ready_threads_mutex, NULL);
	pthread_mutex_init(&data->done_mutex, NULL);
	set_done(data, 0);
}

void	dest_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_ate_mutex);
		pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->ready_threads_mutex);
	pthread_mutex_destroy(&data->done_mutex);
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

t_data	*parse(int ac, char *av[])
{
	t_data	*data;
	int		i;

	if (ac != 5 && ac != 6)
		return (printf("bad number of args\n"), NULL);
	data = malloc(sizeof(t_data));
	get_args(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->nthreads);
	if (!data->philos)
		return (free(data), printf("malloc error\n"), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nthreads);
	if (!data->forks)
		return (free(data->philos), free(data), printf("malloc error\n"), NULL);
	i = -1;
	while (++i < data->nthreads)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
	}
	return (assign_forks(data), data);
}

int	verify(t_data *data, int ac)
{
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
