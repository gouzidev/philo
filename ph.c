/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:16:45 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 01:50:33 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	precise_usleep(long time)
{
	long	start;

	start = millisecons_passed();
	while ((millisecons_passed() - start) < time)
		usleep(500);
}

int	ft_eat(t_data *data, t_philo *philo)
{
	if (get_done(data))
		return (0);
	lock(philo->right_hand);
	safe_print(data, philo->id + 1, "%ld %d has taken a fork\n");
	if (get_done(data))
		return (unlock(philo->right_hand), 0);
	lock(philo->left_hand);
	safe_print(data, philo->id + 1, "%ld %d has taken a fork\n");
	if (get_done(data))
		return (unlock(philo->right_hand), unlock(philo->left_hand), 0);
	set_last_ate(philo, millisecons_passed());
	set_eat_count(philo, get_eat_count(philo) + 1);
	safe_print(data, philo->id + 1, "%ld %d is eating\n");
	precise_usleep(data->time_to_eat);
	if (get_done(data))
		return (unlock(philo->right_hand), unlock(philo->left_hand), 0);
	return (unlock(philo->right_hand), unlock(philo->left_hand), 1);
}

int	ft_sleep(t_data *data, int id)
{
	if (get_done(data))
		return (0);
	safe_print(data, id + 1, "%ld %d is sleeping\n");
	if (get_done(data))
		return (0);
	precise_usleep(data->time_to_sleep);
	if (get_done(data))
		return (0);
	return (1);
}

int	ft_think(t_data *data, int id)
{
	long	curr_timestamp;

	if (get_done(data))
		return (0);
	curr_timestamp = get_timestamp(data);
	if (get_done(data))
		return (0);
	if (get_done(data))
		return (0);
	lock(&data->printf_mutex);
	printf("%ld %d is thinking\n", curr_timestamp, id + 1);
	unlock(&data->printf_mutex);
	return (1);
}
