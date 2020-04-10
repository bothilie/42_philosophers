#include "philo_two.h"

void    ft_exit_thread(t_philo *philo)
{
    pthread_detach(philo->check);
    exit(0);
}

void *living(t_philo *arg)
{
    t_philo *philo;
    philo = (t_philo*)arg;
    if (pthread_create(&philo->check, NULL, check, philo))
        return NULL;
    while(philo->alive)
    {
        print_state(philo, THINKING);
        try_take_fork(philo);
        philo->nb_eat++;
        if (philo->nb_eat >= philo->args->nb_eat && philo->args->nb_eat)
            ft_exit_thread(philo);
        print_state(philo, SLEEPING);
        usleep(1000 * philo->args->t_to_sleep);
    }
    return NULL;
}


void    *check(void *arg)
{
    t_philo *philo;
    philo = (t_philo*)arg;
    struct timeval time;

    while(1)
    {
        sem_wait(philo->sema->sem_philo[philo->index]);
        gettimeofday(&time, NULL);
        int interval;
        interval = (time.tv_sec * 1000 - time.tv_usec / 1000) - philo->last_eat;
        if (interval > philo->args->t_to_die)
        {
            print_state(philo, DIED);
            philo->alive = 0;
            exit(0);
        }
        sem_post(philo->sema->sem_philo[philo->index]);
    }
    return NULL;
}