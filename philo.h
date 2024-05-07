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
}   t_philo;