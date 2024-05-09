#include "philo.h"

// | |
// 0 1

void *routine(void *arg)
{
    int philo_id;
    int nthreads;
    t_philo *philo;
    t_data *data;
    t_fork *forks;

    philo = (t_philo *)arg;
    data = philo->data;
    forks = data->forks;
    philo_id = philo->philo_id;
    nthreads = philo->data->nthreads;
    data->done = 0;
    while (!data->done)
    {
        if (is_odd(philo_id))
        {
            LOCK(&forks[philo_id - 1].fork_mutex);
            philo->left_hand = &forks[philo_id - 1];
            safe_print("%ld %d has taken a fork\n", data, philo_id);
            UNLOCK(&forks[philo_id - 1].fork_mutex);
            LOCK(&forks[philo_id].fork_mutex);
            philo->right_hand = &forks[philo_id];
            safe_print("%ld %d has taken a fork\n", data, philo_id);
            UNLOCK(&forks[philo_id].fork_mutex);
            if (philo->left_hand && philo->right_hand)
            {
                ph_eat(data, philo_id);
                ph_sleep(data, philo_id);
                safe_print("%ld %d is thinking\n", data, philo_id);
            }
        }
        else
        {
            LOCK(&forks[philo_id].fork_mutex);
            philo->left_hand = &forks[philo_id];
            safe_print("%ld %d has taken a fork\n", data, philo_id);
            UNLOCK(&forks[philo_id].fork_mutex);
            if (philo_id != 0)
            {
                LOCK(&forks[philo_id - 1].fork_mutex);
                philo->right_hand = &forks[philo_id - 1];
                safe_print("%ld %d has taken a fork\n", data, philo_id);
                UNLOCK(&forks[philo_id - 1].fork_mutex);
            }
            else
            {
                LOCK(&forks[nthreads - 1].fork_mutex);
                philo->right_hand = &forks[nthreads - 1];
                safe_print("%ld %d has taken a fork\n", data, philo_id);
                UNLOCK(&forks[nthreads - 1].fork_mutex);
            }
            if (philo->left_hand && philo->right_hand)
            {
                ph_eat(data, philo_id);
                ph_sleep(data, philo_id);
                safe_print("%ld %d is thinking\n", data, philo_id);
            }
        }
    }
    return NULL;

}


int main()
{
    int nthreads = 4;
    t_data *data = init_data(nthreads);


    init_fork_mutexes(data);
    create_threads(data, &routine);
    join_threads(data);
    dest_fork_mutexes(data);
}