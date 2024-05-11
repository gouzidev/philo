#include "philo.h"

// | |
// 0 1

void *routine(void *arg)
{
    int philo_id;
    int nthreads;
    t_philo *philo;
    t_data *data;
    pthread_mutex_t *forks;

    philo = (t_philo *)arg;
    data = philo->data;
    forks = data->forks;
    philo_id = philo->philo_id;
    nthreads = philo->data->nthreads;
    while (42)
    {
        check_death(philo);
        if (is_odd(philo_id))
        {
            LOCK(&forks[philo_id - 1]);
            philo->left_hand = &forks[philo_id - 1];
            safe_print("%ld %d has taken a fork\n", data, philo_id);
            UNLOCK(&forks[philo_id - 1]);
            LOCK(&forks[philo_id]);
            philo->right_hand = &forks[philo_id];
            safe_print("%ld %d has taken a fork\n", data, philo_id);
            UNLOCK(&forks[philo_id]);
            if (philo->left_hand && philo->right_hand)
            {
                ph_eat(data, philo_id);
                ph_sleep(data, philo_id);
                safe_print("%d is thinking\n", data, philo_id);
            }
        }
        else
        {
            LOCK(&forks[philo_id]);
            philo->left_hand = &forks[philo_id];
            safe_print("%ld %d has taken a fork\n", data, philo_id);
            UNLOCK(&forks[philo_id]);
            if (philo_id != 0)
            {
                LOCK(&forks[philo_id - 1]);
                philo->right_hand = &forks[philo_id - 1];
                safe_print("%ld %d has taken a fork\n", data, philo_id);
                UNLOCK(&forks[philo_id - 1]);
            }
            else
            {
                LOCK(&forks[nthreads - 1]);
                philo->right_hand = &forks[nthreads - 1];
                safe_print("%ld %d has taken a fork\n", data, philo_id);
                UNLOCK(&forks[nthreads - 1]);
            }
            if (philo->left_hand && philo->right_hand)
            {
                ph_eat(data, philo_id);
                ph_sleep(data, philo_id);
                safe_print("%d is thinking\n", data, philo_id);
            }
        }
    }
    return NULL;

}


int main(int ac, char *av[])
{
    t_data *data = init_data(ac, av);
    init_fork_mutexes(data);
    create_threads(data, &routine);
    join_threads(data);
    dest_fork_mutexes(data);
}