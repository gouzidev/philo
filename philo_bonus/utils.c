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

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

void	safe_print(t_data *data, int id, char *msg)
{
	long	curr_timestamp;

	curr_timestamp = get_timestamp(data);
	sem_wait(data->print_sem);
	printf(msg, curr_timestamp, id + 1);
	sem_post(data->print_sem);
}

int	will_die(t_philo *philo)
{
	int		should_die;
	long	time_since_ate;
	long	time_to_die;

	time_to_die = philo->data->time_to_die;
	time_since_ate = (millisecons_passed() - get_last_ate(philo));
	should_die = time_since_ate > time_to_die;
	return (should_die);
}

void waiter(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	while(i < data->nthreads)
	{
		waitpid(-1, &status, 0);
		if (status >> 8 == 0)
			return ;
		else
			kill_all(data);
		i++;
	}
}

void init_semaphores(t_data *data)
{
	sem_unlink("/print");
	data->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("/forks");
	data->forks_sem = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nthreads);
	sem_unlink("/start");
	data->start_sem = sem_open("/start", O_CREAT | O_EXCL, 0644, 0);
}

void close_semaphores(t_data *data)
{
	(void) data;
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/start");
}