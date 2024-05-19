#include "philo.h"

void LOCK(pthread_mutex_t *thread)
{
    pthread_mutex_lock(thread);
}

void UNLOCK(pthread_mutex_t *thread)
{
    pthread_mutex_unlock(thread);
}

long millisecons_passed()
{
    struct timeval now;
    long time_mille;
    gettimeofday(&now, NULL);
    time_mille = (now.tv_sec * 1000) + (now.tv_usec / 1000);
    return time_mille;
}

long get_timestamp(t_data *data)
{
    return millisecons_passed() - data->init_time;
}