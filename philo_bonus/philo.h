/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgouzi <sgouzi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 01:30:16 by sgouzi            #+#    #+#             */
/*   Updated: 2024/05/20 03:50:46 by sgouzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>
# include <semaphore.h>
#include <wait.h>
#include <sys/wait.h>
#include <signal.h>


typedef struct s_data	t_data;
typedef struct s_philo	t_philo;
typedef struct s_fork	t_fork;

typedef struct s_data
{
	t_philo				*philos;
	int					nthreads;
	sem_t				*print_sem;
	sem_t				*forks_sem;
	sem_t				*running_sem;
	sem_t				*start_sem;
	long				running;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				init_time;
	long				n_eat_times;
	pid_t				*pids;
}						t_data;

typedef struct s_philo
{
	int					id;
	long				time_eat;
	long				time_sleep;
	long				time_think;
	long				time_die;

	long				last_ate;
	sem_t				*last_ate_sem;
	char				*last_ate_name;
	long				eat_count;
	sem_t				*eat_count_sem;
	char				*eat_count_name;
	t_data				*data;
}						t_philo;

/* safe.c */
long					get_eat_count(t_philo *philo);
long					get_last_ate(t_philo *philo);

void					set_eat_count(t_philo *philo, long new_eat_count);
void					set_last_ate(t_philo *philo, long new_last_ate);
long					get_running(t_data *data);
void					set_running(t_data *data, long new_running);

int						ft_atoi(const char *str);
t_data					*parse(int ac, char *av[]);
int						verify(t_data *data, int ac);
long					millisecons_passed(void);
long					get_timestamp(t_data *data);
int						will_die(t_philo *philo);
/* ph.c */
int						ft_think(t_data *data, t_philo *philo);
int						ft_eat(t_data *data, t_philo *philo);
int						ft_sleep(t_data *data, t_philo *philo);
/* utils.c */
int						ft_atoi(const char *str);
void					safe_print(t_data *data, int id, char *msg);

/* utils1.c */
void					precise_usleep(long n);
int						freee(t_data *data);

void procecss(t_philo *philo);
void kill_all(t_data *data);
void	*observer(void *arg);




/* init.c */

void init_semaphores(t_data *data);
void close_semaphores(t_data *data);
void waiter(t_data *data);
#endif