#include "philo.h"

void while_true(t_data *data, int id)
{
    int sig;
    while (!get_done(data))
    {
        LOCK(&data->printf_mutex);
        printf("%ld %d is fucking\n", get_timestamp(data), id);
        UNLOCK(&data->printf_mutex);
        if (get_done(data))
            break;
        sig = decide_first_fork(data, id);
        if (sig != -1 && !get_done(data))
            ph_sleep(data, id);
    }
    return ;
}
void observer(t_data *data)
{
    int i;
    while (get_ready_threads_count(data) != data->nthreads);
    while (!get_done(data))
    {
        i = 0;
        while (i < data->nthreads)
        {
            if (get_curr_time() - get_last_ate(&data->philos[i]) > data->time_to_die)
            {
                set_done(data, 1);
                LOCK(&data->printf_mutex);
                printf("%ld %d died\n", get_timestamp(data), i);
                UNLOCK(&data->printf_mutex);
                break;
            }
            i++;
        }
    }
}

void *routine(void *arg)
{
    // increment ready_threads_count

    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;
    set_used_forks(philo, 0);
        LOCK(&data->printf_mutex);
    printf("Thread %d is ready\n", philo->id);
    UNLOCK(&data->printf_mutex);
    while (get_ready_threads_count(data) != data->nthreads);
    LOCK(&data->printf_mutex);
    printf("Thread %d is starting\n", philo->id);
    UNLOCK(&data->printf_mutex);
    while_true(data, philo->id);
    LOCK(&data->printf_mutex);
    printf("Thread %d is done\n", philo->id);
    UNLOCK(&data->printf_mutex);
    if (get_used_fork(philo) == 1)
        UNLOCK(&data->forks[philo->id]);
    return NULL;
}

int main(int ac, char *av[])
{
    t_data *data;

    data = parse(ac, av);
    init_data(data);
    init_mutexes(data);
    set_done(data, 0);
    set_started(data, 0);
    set_ready_threads_count(data, 0);
    create_threads(data, routine);
    observer(data);
    join_threads(data);
    printf("All threads joined\n");
    dest_mutexes(data);
}