#include "philo.h"

// | |
// 0 1

void *routine(void *arg)
{
    int philo_id;
    int nthreads;
    t_philo *philo;

    philo = (t_philo *)arg;
    philo_id = philo->philo_id;
    nthreads = philo->data->nthreads;
    if (is_odd(philo_id))
    {
        pthread_mutex_lock(&philo->data->forks[philo_id - 1].fork_mutex);
        philo->left_hand = &philo->data->forks[philo_id - 1];
        pthread_mutex_unlock(&philo->data->forks[philo_id - 1].fork_mutex);
        pthread_mutex_lock(&philo->data->forks[philo_id].fork_mutex);
        philo->right_hand = &philo->data->forks[philo_id];
        pthread_mutex_unlock(&philo->data->forks[philo_id].fork_mutex);
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[philo_id].fork_mutex);
        philo->left_hand = &philo->data->forks[philo_id];
        pthread_mutex_unlock(&philo->data->forks[philo_id].fork_mutex);
        if (philo_id != 0)
        {
            pthread_mutex_lock(&philo->data->forks[philo_id - 1].fork_mutex);
            philo->right_hand = &philo->data->forks[philo_id - 1];
            pthread_mutex_unlock(&philo->data->forks[philo_id - 1].fork_mutex);
        }
        else
        {
            pthread_mutex_lock(&philo->data->forks[philo_id - 1].fork_mutex);
            philo->right_hand = &philo->data->forks[philo_id - 1];
            pthread_mutex_unlock(&philo->data->forks[philo_id - 1].fork_mutex);
        }
    }
    return NULL;
}


int main()
{
    int nthreads = 4;
    t_data *data = init_data(nthreads);
    int i = 0;

    init_fork_mutexes(data);
    while (i < nthreads)
    {
        pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
        i++;
    }
    dest_fork_mutexes(data);
    
}