/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:15:55 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 09:59:00 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data, void *(*routine)(void *))
{
	int	i;

	i = 0;
	set_ready_threads(data, 0);
	while (i < data->nthreads)
	{
		set_last_ate(&data->philos[i], millisecons_passed());
		set_eat_count(&data->philos[i], 0);
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
		set_ready_threads(data, get_ready_threads(data) + 1);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	observer(t_data *data)
{
	int	i;
	int	full_philos;

	while (get_ready_threads(data) < data->nthreads)
		;
	while (1)
	{
		i = -1;
		full_philos = 0;
		while (++i < data->nthreads)
		{
			if (get_eat_count(&data->philos[i]) == data->n_eat_times)
			{
				full_philos++;
				if (full_philos == data->nthreads)
					return (set_done(data, 1), 1);
			}
			if (will_die(&data->philos[i]))
			{
				safe_print(data, data->philos[i].id + 1, "%ld %d died\n");
				return (set_done(data, 1), 1);
			}
		}
	}
}

void	*routine(void *arg)
{
	int		ate;
	int		slept;
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (get_ready_threads(data) < data->nthreads)
		;
	if (philo->id % 2)
		precise_usleep(20);
	while (1)
	{
		ate = ft_eat(data, philo);
		if (!ate)
			return (NULL);
		slept = ft_sleep(data, philo->id);
		if (!slept)
			return (NULL);
		ft_think(data, philo->id);
		if (get_done(data))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_data	*data;
	int		good;

	data = parse(ac, av);
	good = verify(data, ac);
	if (!good)
		return (printf("bad args\n"), free(data->forks), free(data->philos),
			free(data), 1);
	init_mutexes(data);
	set_done(data, 0);
	data->init_time = millisecons_passed();
	create_threads(data, routine);
	observer(data);
	join_threads(data);
	dest_mutexes(data);
	free(data->forks);
	free(data->philos);
	free(data);
	return (0);
}
