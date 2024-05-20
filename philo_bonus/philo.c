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

void waiter(t_data *data)
{
	int	status;
	pid_t	dead_child;
	int	i;

	i = 0;
	while(i < data->nthreads)
	{
		dead_child = waitpid(-1, &status, 0);
		i++;
	}
}

void	*observer(void *arg)
{
	t_data *data;
	t_philo *philo;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (get_eat_count(philo) == data->n_eat_times)
		{
			set_alive(philo, 1);
			return NULL;
		}
		if (will_die(philo))
		{
			safe_print(data, philo->id + 1, "%ld %d died\n");
			set_alive(philo, 1);
			return NULL;
		}
	}
	return NULL;
}

void ft_eat(t_data *data, t_philo *philo)
{
	if (!get_alive(philo))
		return;

	sem_wait(data->forks_sem);
	safe_print(data, philo->id, "%ld %d has taken a fork\n");
	if (!get_alive(philo))
	{
		sem_post(data->forks_sem);
		return ;
	}
	sem_wait(data->forks_sem);
	safe_print(data, philo->id, "%ld %d has taken a fork\n");
	if (!get_alive(philo))
	{
		sem_post(data->forks_sem);
		sem_post(data->forks_sem);
		return ;
	}
	safe_print(data, philo->id, "%ld %d is eating\n");
	// set_last_ate(philo, millisecons_passed());
	// set_eat_count(philo, get_eat_count(philo) + 1);
	if (!get_alive(philo))
	{
		sem_post(data->forks_sem);
		sem_post(data->forks_sem);
		return ;
	}
	precise_usleep(data->time_to_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);

}

void ft_sleep(t_data *data, t_philo *philo)
{
	if (!get_alive(philo))
		return ;
	safe_print(data, philo->id, "%ld %d is sleeping\n");
	if (!get_alive(philo))
		return ;
	precise_usleep(data->time_to_sleep);
}

void ft_think(t_data *data, t_philo *philo)
{
	if (!get_alive(philo))
		return ;
	safe_print(data, philo->id, "%ld %d is thinking\n");
	if (!get_alive(philo))
		return ;
	precise_usleep(data->time_to_sleep);
}

void process(t_philo *philo) // routine
{
	pthread_t thread;
	t_data *data;
	printf("-> %d\n", philo->id);

	data = philo->data;
	philo->alive_sem = sem_open("/alive", O_CREAT, 0644, 1);
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	data->forks_sem = sem_open("/philos", O_CREAT, 0644, data->nthreads);
	set_alive(philo, 1);

	pthread_create(&thread, NULL, observer, philo);
	while(get_alive(philo))
	{
		ft_eat(data, philo);
		// ft_sleep(data, philo);
		// ft_think(data, philo);
		sem_wait(data->print_sem);
		printf("hey\n");
		sem_post(data->print_sem);
		precise_usleep(6000);
	}
	pthread_join(thread, NULL);
	sem_close(philo->alive_sem);
	sem_close(data->print_sem);
	sem_close(data->forks_sem);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	int	good;
	int i;
	int id;

	data = parse(ac, av);
	good = verify(data, ac);
	if (!good)
		return (free(data->philos), free(data), 1);
	i = 0;
	while (i < data->nthreads)
	{
		id = fork();
		if (id == 0)
			process(&data->philos[i]);
		else if (id == -1)
			return (freee(data));
		else
			data->pids[i] = id;
		i++;
	}
	waiter(data);
	return freee(data);
}
