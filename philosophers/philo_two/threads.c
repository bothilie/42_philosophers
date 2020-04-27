#include "philo_two.h"

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
    gl->num_philo--;
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
        sem_wait(gl->sema->sem_philo);
        if (get_time() - philo->last_eat > (unsigned long)gl->args->t_to_die)
        {
            print_state(philo, DIED);
            sem_wait(gl->sema->died);
            gl->alive = 0;
            sem_post(gl->sema->died);
            break ;
        }
        sem_post(gl->sema->sem_philo);
        ft_sleeping(10);
    }
    return NULL;
}

int     try_take_fork(t_philo *philo)
{
    t_global *gl;

    gl = get_gl();
    sem_wait(gl->sema->take);
    sem_wait(gl->sema->forks);
    print_state(philo, TAKE_FORK);
    sem_wait(gl->sema->forks);
    print_state(philo, TAKE_FORK);
    sem_post(gl->sema->take);
    sem_wait(gl->sema->sem_philo);
    philo->last_eat = get_time();
    sem_post(gl->sema->sem_philo);
    print_state(philo, EATING);
    ft_sleeping(gl->args->t_to_sleep);
    sem_wait(gl->sema->put);
    sem_post(gl->sema->forks);
    sem_post(gl->sema->forks);
    sem_post(gl->sema->put);
    return 1;
}

t_global    *get_gl()
{
    static t_global gl;
    return (&gl);
}