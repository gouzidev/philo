#include "philo.h"

int will_die(t_philo *philo)
{
    long time_to_die;

    time_to_die = philo->data->time_to_die;
    return (get_curr_time() - get_last_ate(philo) > time_to_die);
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
            if (will_die(&data->philos[i]))
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
    while (get_ready_threads_count(data) != data->nthreads);
    while (!get_done(data))
    {
        do_routine(data, philo->id);
    }
    
    return NULL;
}

void *lone_philo_routine(t_data *data)
{
    while (1)
    {
        ft_think(data, 0);
        ft_eat(data, 0);
        ft_sleep(data, 0);
    }
    return NULL;
}

int main(int ac, char *av[])
{
    t_data *data;

    data = parse(ac, av);
    init_data(data);
    init_mutexes(data);
    set_done(data, 0);
    set_ready_threads_count(data, 0);
    set_started(data, 0);
    create_threads(data, routine);
    observer(data);
    join_threads(data);
    printf("All threads joined\n");
    dest_mutexes(data);
}