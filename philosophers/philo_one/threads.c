#include "philo_one.h"

void *living(void *arg)
{
    t_philo *philo;
    philo = (t_philo*)arg;
    t_global *gl;

    gl = get_gl();
    while(1)
    {
        print_state(philo, THINKING);
        try_take_fork(philo);
        philo->nb_eat++;
        if (gl->args->nb_eat && philo->nb_eat >= gl->args->nb_eat)
            break ;
        print_state(philo, SLEEPING);
        ft_sleeping(gl->args->t_to_sleep);
    }
    return NULL;
}


void    *check(void *arg)
{
    t_philo *philo;
    philo = (t_philo*)arg;
    t_global *gl;

    gl = get_gl();
    while(1)
    {
        pthread_mutex_lock(&gl->sema->sem_philo[philo->index]);
        if (get_time() - philo->last_eat > (unsigned long)gl->args->t_to_die)
        {
            print_state(philo, DIED);
            pthread_mutex_lock(&gl->sema->died);
            gl->alive = 0;
            pthread_mutex_unlock(&gl->sema->died);
            break ;
        }
        pthread_mutex_unlock(&gl->sema->sem_philo[philo->index]);
        ft_sleeping(10);
    }
    return NULL;
}

int     try_take_fork(t_philo *philo)
{
    t_global *gl;

    gl = get_gl();
    pthread_mutex_lock(&gl->sema->take);
    pthread_mutex_lock(&gl->sema->forks[philo->index]);
    print_state(philo, TAKE_FORK);
    pthread_mutex_lock(&gl->sema->forks[(philo->index + 1) % gl->args->nb_philo]);
    print_state(philo, TAKE_FORK);
    pthread_mutex_unlock(&gl->sema->take);
    pthread_mutex_lock(&gl->sema->sem_philo[philo->index]);
    philo->last_eat = get_time();
    pthread_mutex_unlock(&gl->sema->sem_philo[philo->index]);
    print_state(philo, EATING);
    ft_sleeping(gl->args->t_to_sleep);
    pthread_mutex_lock(&gl->sema->put);
    pthread_mutex_unlock(&gl->sema->forks[philo->index]);
    pthread_mutex_unlock(&gl->sema->forks[(philo->index + 1) % gl->args->nb_philo]);
    pthread_mutex_unlock(&gl->sema->put);
    return 1;
}

t_global    *get_gl()
{
    static t_global gl;
    return (&gl);
}