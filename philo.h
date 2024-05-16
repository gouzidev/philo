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
    pthread_mutex_t *forks;
    int nthreads;
    long done;
    pthread_mutex_t done_mutex;
    long started;
    pthread_mutex_t started_mutex;
    pthread_mutex_t printf_mutex;
    pthread_mutex_t time_mutex;
    int ready_threads_count;
    pthread_mutex_t ready_threads_count_mutex;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long time;
    long time_stamp;
    long init_time;
    long n_eat_times;
}   t_data;

typedef struct s_philo
{
    int id;
    long init_time;
    long time_eat;
    long time_sleep;
    long time_think;
    long time_die;
    long last_ate;
    int gonna_die;
    long used_forks;

    long eat_count;
    pthread_mutex_t     last_ate_mutex;
    pthread_mutex_t     used_forks_mutex;
    pthread_mutex_t     eat_count_mutex;
    pthread_t thread;
    pthread_mutex_t     *right_hand;
    pthread_mutex_t     *left_hand;
    t_data      *data;
} t_philo;

/* safe.c */
long    get_done(t_data *data);
long    get_started(t_data *data);
long    get_time(t_data *data);
long    get_ready_threads_count(t_data *data);
long    get_eat_count(t_philo *philo);
long    get_last_ate(t_philo *philo);
long    get_used_fork(t_philo *philo);

void    set_done(t_data *data, long new_done);
void    set_started(t_data *data, long new_started);
void    set_time(t_data *data, long new_time);
void    set_ready_threads_count(t_data *data, long new_ready_threads_count);
void    set_eat_count(t_philo *philo, long new_eat_count);
void    set_last_ate(t_philo *philo, long new_last_ate);
void set_used_forks(t_philo *philo, long new_used_forks);

int	ft_atoi(const char *str);
int is_odd(int n);
// void print(char *msg,t_data *data, int id);
void init_mutexes(t_data *data);
void create_threads(t_data *data, void *(*routine)(void *));
void join_threads(t_data *data);
void assign_forks(t_data *data);
t_data *parse(int ac, char *av[]);
void init_data (t_data *data);
void dest_mutexes(t_data *data);
void ph_eat(t_data *data, int id);
void ph_sleep(t_data *data, int id);
void ph_think(t_data *data, int id);
void ph_die(t_data *data, int id);
void LOCK(pthread_mutex_t *thread);
void UNLOCK(pthread_mutex_t *thread);
long get_curr_time();
long get_timestamp(t_data *data);
int gonna_die(t_data *data, int ph_id);

int decide_first_fork(t_data *data, int id);
void *routine(void *arg);
void while_true(t_data *data, int id);
void setup_thread(t_data *data);
/* ph.c */
void ph_think(t_data *data, int id);
void ph_eat(t_data *data, int id);
void ph_sleep(t_data *data, int id);
void ph_die(t_data *data, int id);
int gonna_die(t_data *data, int ph_id);

/* utils.c */
int	ft_atoi(const char *str);
void safe_print(t_data *data, int id, char *msg);

/* utils1.c */
int is_odd(int n);
void LOCK(pthread_mutex_t *thread);
void UNLOCK(pthread_mutex_t *thread);
long get_curr_time();
long get_timestamp(t_data *data);

#endif