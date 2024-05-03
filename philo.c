#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo {
    int i;
    pthread_t *t;
    pthread_mutex_t mutex;
}   t_philo;

void *print_n(void *p)
{
    t_philo *ph;

    ph = (t_philo *)p;

    pthread_mutex_lock(&ph->mutex);
    printf("-> %d\n", (ph->i)++);
    pthread_mutex_unlock(&ph->mutex);

}

int main()
{
    t_philo p;
    p.t = malloc(sizeof(pthread_t) * 10);
    pthread_mutex_init(&p.mutex, NULL);
    int i = 0;
    while (i < 10)
    {
        pthread_create(&p.t[i], NULL, print_n, &p);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(p.t[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&p.mutex);
}