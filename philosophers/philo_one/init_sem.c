#include "philo_one.h"

sem_t   *init_mutex(t_arg *args, int i, char *nom)
{
    char *tmp;
    char *name;
    sem_t *dest;

    tmp = ft_itoa(i);
    name = ft_strjoin(nom, tmp);
    sem_unlink(name);
    if (!(dest = sem_open(name, O_CREAT, 0666, 1)))
        return NULL;
    free(name);
    free(tmp);
    return dest;
}

t_sem *init_sem(t_arg *args) // Protéger les sema open
{
    int i;
    t_sem *lock;

    i = -1;
    if (!(lock = (t_sem*)malloc(sizeof(t_sem))))
        return NULL;
    pthread_mutex_init(&lock->stdout, NULL);
    pthread_mutex_init(&lock->died, NULL);
    pthread_mutex_init(&lock->take, NULL);
    pthread_mutex_init(&lock->put, NULL);
   if (!(lock->sem_philo = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
        return NULL;
     if (!(lock->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->nb_philo)))
        return NULL;
    while (++i < args->nb_philo)
    {
        pthread_mutex_init(&lock->sem_philo[i], NULL);
        pthread_mutex_init(&lock->forks[i], NULL);
    }
    return lock;
}