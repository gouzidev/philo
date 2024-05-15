#include "philo.h"

void *monitoring(void *arg)
{
    t_data *data;
    int i;
    data = (t_data *)arg;
    while (!get_started(data));
    while (!get_done(data))
    {
        i = -1;
        while (++i < data->nthreads && !get_done(data))
        {
            if (gonna_die(data, i))
            {
                ph_die(data, i);
                break;
            }
        }
    }
    return (NULL);
}

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

void setup_thread(t_data *data)
{
    long ready_threads_count;
    ready_threads_count = get_ready_threads_count(data);
    set_ready_threads_count(data, ready_threads_count + 1);
    ready_threads_count = get_ready_threads_count(data);
    if (ready_threads_count == data->nthreads)
        set_started(data, 1);
}

void *routine(void *arg)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;
    setup_thread(data);
    while (!get_started(philo->data));
    while_true(data, philo->id);
    return NULL;
}

int main(int ac, char *av[])
{
    t_data *data;

    data = parse(ac, av);
    init_data(data);
    init_mutexes(data);
    create_threads(data, routine);
    join_threads(data);
    dest_mutexes(data);
}