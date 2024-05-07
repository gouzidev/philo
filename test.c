#include "philo.h"

void    *routine(void   *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    printf("philosopher -> %d\n", philo->number);
}

pthread_t   *init_threads(int   n_threads)
{
    pthread_t *threads;
    int i;

    threads = malloc(sizeof(pthread_t) * (n_threads + 1));
    i = 0;
    while (i < n_threads)
    {
        pthread_create(&threads[i], NULL, )
        threads[i]
    }

}

int main(int    ac, char    *av[],  char    *env[])
{
    pthread_mutex_t forks_mutex;
    if (ac < 5 || ac > 6)
        (write(2, "wrong number of args\n", 22), exit(1));
    

    

    int i;

    i = 0;
    while (i < n_philos)
    {
        
    }
    return 0;
}