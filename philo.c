#include "philo.h"

void while_true(t_data *data, int id)
{
    while (!get_done(data))
    {
        if (!get_done(data))
            ph_eat(data, id);
        if (!get_done(data))
            ph_think(data, id);
    }
    return ;
}
void observer(t_data *data)
{
    int i;
    while (get_ready_threads_count(data) != data->nthreads)
    {
        LOCK(&data->printf_mutex);
        printf("waiting for threads to start\n");
        UNLOCK(&data->printf_mutex);
        usleep(1);
    }
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
    while (get_ready_threads_count(data) != data->nthreads)
        usleep(1);
    while_true(data, philo->id);
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
    dest_mutexes(data);
}