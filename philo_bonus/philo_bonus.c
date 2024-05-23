/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:15:55 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/24 00:47:45 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*observer(void *arg)
{
	t_data			*data;
	t_philo			*philo;
	struct timeval	now;
	long			now_mille;
	long			last_ate_mille;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		gettimeofday(&now, NULL);
		now_mille = (now.tv_sec * 1000) + (now.tv_usec / 1000);
		last_ate_mille = (philo->last_ate.tv_sec * 1000)
			+ (philo->last_ate.tv_usec / 1000);
		if (now_mille - last_ate_mille > data->time_to_die)
		{
			sem_wait(data->print_sem);
			printf("%ld %d died\n", get_timestamp(data), philo->id + 1);
			freee(data);
			exit(1);
		}
	}
	return (NULL);
}

int	ft_eat(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0);
	sem_wait(data->forks_sem);
	safe_print(data, philo->id, "%ld %d has taken a left  fork\n");
	if (!get_running(data))
		return (sem_post(data->forks_sem), 0);
	sem_wait(data->forks_sem);
	safe_print(data, philo->id, "%ld %d has taken a right fork\n");
	if (!get_running(data))
		return (sem_post(data->forks_sem), sem_post(data->forks_sem), 0);
	safe_print(data, philo->id, "%ld %d is eating\n");
	sem_wait(data->print_sem);
	gettimeofday(&philo->last_ate, NULL);
	philo->meals_eaten++;
	sem_post(data->print_sem);
	precise_usleep(data->time_to_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	if ((data->n_eat_times != -1) && (philo->meals_eaten == data->n_eat_times))
	{
		data->running = 0;
		exit(0);
	}
	return (1);
}

int	ft_sleep(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0);
	safe_print(data, philo->id, "%ld %d is sleeping\n");
	if (!get_running(data))
		return (0);
	precise_usleep(data->time_to_sleep);
	return (1);
}

int	ft_think(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0);
	safe_print(data, philo->id, "%ld %d is thinking\n");
	if (!get_running(data))
		return (0);
	precise_usleep(1);
	return (1);
}

void	process(t_philo *philo) // routine
{
	t_data		*data;
	int			good;
	pthread_t	thread;

	data = philo->data;
	if (philo->id % 2 == 0)
		precise_usleep(1);
	gettimeofday(&philo->last_ate, NULL);
	set_running(data, 1);
	philo->meals_eaten = 0;
	pthread_create(&thread, NULL, observer, philo);
	while (1)
	{
		good = ft_eat(data, philo);
		if (!good)
			break ;
		good = ft_sleep(data, philo);
		if (!good)
			break ;
		good = ft_think(data, philo);
		if (!good)
			break ;
	}
	pthread_join(thread, NULL);
}
