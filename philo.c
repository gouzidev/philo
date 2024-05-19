#include "philo.h"

int will_die(t_philo *philo)
{
    int should_die;
    long time_since_ate;
    long time_to_die;

    time_to_die = philo->data->time_to_die;
    time_since_ate = (millisecons_passed() - get_last_ate(philo));
    should_die = time_since_ate > time_to_die;
    return (should_die);
}


void observer(t_data *data)
{
    int i;
    while (get_ready_threads(data) < data->nthreads);
    while (1)
    {
        i = 0;
        while (i < data->nthreads)
        {
            if (will_die(&data->philos[i]))
            {
                safe_print(data, data->philos[i].id + 1, "%ld %d died\n");
                LOCK(&data->done_mutex);
                data->done = 1;
                UNLOCK(&data->done_mutex);
                return ;
            }
            i++;
        }
    }
}

void *routine(void *arg)
{
    int ate;
    int slept;
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;
    while (get_ready_threads(data) < data->nthreads);
    if (philo->id % 2)
        precise_usleep(NULL, 20);
    while (1)
    {
        ate = ft_eat(data, philo);
        if (!ate)
            return NULL;
        if (get_done(data))
            return NULL;
        slept = ft_sleep(data, philo->id);
        if (!slept)
            return NULL;
        if (get_done(data))
            return NULL;
        ft_think(data, philo->id);
        if (get_done(data))
            return NULL;
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
    data->init_time = millisecons_passed();
    create_threads(data, routine);
    observer(data);
    join_threads(data);
    dest_mutexes(data);
}