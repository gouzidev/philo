/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:42 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 01:50:27 by sgouzi           ###   ########.fr       */
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

t_data	*parse(int ac, char *av[])
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		(printf("bad number of args\n"), exit(1));
	data = malloc(sizeof(t_data));
    data->nthreads = ft_atoi(av[1]);
    data->time_to_die = ft_atoi(av[2]);
    data->time_to_eat = ft_atoi(av[3]);
    data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_eat_times = ft_atoi(av[5]);
	else
		data->n_eat_times = -1;
	return (data);
}

void	init_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nthreads);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nthreads);
	i = -1;
	while (++i < data->nthreads)
	{
		data->philos[i].data = data;
		data->philos[i].id = i;
	}
	assign_forks(data);
}

void	assign_forks(t_data *data)
{
	int	i;
	int	nphilos;

	nphilos = data->nthreads;
	i = -1;
	if (nphilos == 1)
	{
		data->philos[0].right_hand = &data->forks[0];
		data->philos[0].left_hand = NULL;
		return ;
	}
	while (++i < data->nthreads)
	{
		data->philos[i].right_hand = &data->forks[i];
		data->philos[i].left_hand = &data->forks[(i + 1) % nphilos];
	}
}
