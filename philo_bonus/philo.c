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


void kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nthreads)
	{
		kill(data->pids[i], SIGKILL);
		i++;
	}
	sem_post(data->print_sem);
}

void	*observer(void *arg)
{
	t_data *data;
	t_philo *philo;
    long last_ate;

	philo = (t_philo *)arg;
	data = philo->data;

	while (1)
	{
		sem_wait(philo->last_ate_sem);
        last_ate = philo->last_ate;
        sem_post(philo->last_ate_sem);
		sem_wait(data->print_sem); // replace will die with hard code
		if (last_ate != 0 && will_die(philo))
		{
			printf("%ld %d died\n", get_timestamp(data), philo->id);
			freee(data);
			sem_post(data->print_sem);
			exit(1);
		}
		sem_post(data->print_sem);
	}
	return NULL;
}

int ft_eat(t_data *data, t_philo *philo)
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
	sem_wait(data->print_sem);
	printf("%ld %d is eating\n", get_timestamp(data), philo->id);
    philo->last_ate = millisecons_passed(); // use gettimeoftheday nichan
	philo->eat_count++;
	sem_post(data->print_sem);
	precise_usleep(data->time_to_eat);
	sem_post(data->forks_sem);
	sem_post(data->forks_sem);
	if (data->n_eat_times == get_eat_count(philo))
		exit(0);
	return (1);
}

int ft_sleep(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0) ;
	safe_print(data, philo->id, "%ld %d is sleeping\n");
	if (!get_running(data))
		return (0) ;
	precise_usleep(data->time_to_sleep);
	return (1);
}

int ft_think(t_data *data, t_philo *philo)
{
	if (!get_running(data))
		return (0);
	safe_print(data, philo->id, "%ld %d is thinking\n");
	if (!get_running(data))
		return (0);
	precise_usleep(1);
	return (1);
}

void process(t_philo *philo) // routine
{
	t_data *data;
	int good;
	pthread_t thread;

	data = philo->data;
	if (philo->id % 2 == 0)
	 	precise_usleep(1);
	sem_wait(data->print_sem);
	philo->last_ate = millisecons_passed();
	sem_post(data->print_sem);
	set_eat_count(philo, 0);
	set_running(data, 1);
	pthread_create(&thread, NULL, observer, philo);
	while(1)
	{
		good = ft_eat(data, philo);
		if (!good)
			break;
		good = ft_sleep(data, philo);
		if (!good)
			break;
		good = ft_think(data, philo);
		if (!good)
			break;
	}
	pthread_join(thread, NULL);
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
		return (printf("bad args\n"), free(data->philos), free(data), 1);
	init_semaphores(data);
	data->init_time = millisecons_passed();
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
	close_semaphores(data);
	return freee(data);
}
