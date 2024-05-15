#include "philo.h"

void *monitoring(void *arg)
{
    t_data *data;
    long started;
    int i;
    data = (t_data *)arg;
    safe_print(data, -1, "sffsfsdfdsfdsf\n");
    started = get_started(data);
    while (!started)
    {
        started = get_started(data);
        LOCK(&data->printf_mutex);
        printf("started = %ld\n", data->started);
        printf("nthreads = %d\n", data->nthreads);
        UNLOCK(&data->printf_mutex);
    }
    
    usleep(1);
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
    set_ready_threads_count(data, get_ready_threads_count(data) + 1);
    if (get_ready_threads_count(data) == data->nthreads)
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