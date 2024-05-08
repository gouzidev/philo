#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philo
{
    int number;
    int time_die;
    int time_eat;
    int time_sleep;
    pthread_t thread;
    pthread_mutex_t *forks_mutex;

}   t_philo;

typedef struct s_data
{
    t_philo *philos;
    
}   t_data;