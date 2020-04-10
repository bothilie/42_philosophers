#include "philo_two.h"

void    ft_exit_thread(t_philo *philo)
{
    //unlink()
    //pthread_detach(philo->check);
    //pthread_detach(philo->living);
}

void *living(void *arg)
{
    t_philo *philo;
    philo = (t_philo*)arg;
    
    while(philo->alive)
    {
        print_state(philo, THINKING);
        try_take_fork(philo);
        philo->nb_eat++;
        if (philo->nb_eat >= philo->args->nb_eat)
        {
            philo->alive = 0;
            return NULL;
        }
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

    while(philo->alive)
    {
        sem_wait(philo->sema->sem_philo[philo->index]);
        gettimeofday(&time, NULL);
        int interval;
        interval = (time.tv_sec * 1000 - time.tv_usec / 1000) - philo->last_eat;
        if (interval > philo->args->t_to_die)
        {
            print_state(philo, DIED);
            philo->alive = 0;
           ft_exit_thread(philo);
           return NULL;
        }
        sem_post(philo->sema->sem_philo[philo->index]);
    }
    return NULL;
}