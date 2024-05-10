#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data t_data;
typedef struct s_philo t_philo;
typedef struct s_fork t_fork;


typedef struct s_data
{
    t_philo *philos;
    t_fork *forks;
    long time;
    long start_time;
    struct timeval *curr_time;
    int nthreads;
    int done;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long n_eat_times;
    pthread_mutex_t printf_mutex;
}   t_data;

typedef struct s_fork
{
    pthread_mutex_t fork_mutex;
    int fork_n;
    int busy;
}   t_fork;

typedef struct s_philo
{
    int philo_id;
    long time_eat;
    long time_sleep;
    long time_think;
    long time_die;
    int is_dead;
    pthread_t thread;
    t_fork     *right_hand;
    t_fork     *left_hand;
    t_data      *data;
} t_philo;


int	ft_atoi(const char *str);
int is_odd(int n);
void safe_print(char *msg,t_data *data, int philo_id);
void init_fork_mutexes(t_data *data);
void create_threads(t_data *data, void *(*routine)(void *));
void join_threads(t_data *data);
t_data *init_data (int ac, char *av[]);
void dest_fork_mutexes(t_data *data);
void ph_eat(t_data *data, int philo_id);
void ph_sleep(t_data *data, int philo_id);
void LOCK(pthread_mutex_t *thread);
void UNLOCK(pthread_mutex_t *thread);
#endif