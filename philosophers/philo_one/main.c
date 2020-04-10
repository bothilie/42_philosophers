#include "philo_two.h"

int main(int argc, char **argv)
{
    t_arg   *args;
    t_sem *sema;
    t_philo    *philo;
    int i;

    if (argc < 5 || argc > 6)
    {
        write(1, "Not good number of arguments\n", 29);
        return 1;
    }
    if (!(args = parse_args(argc, argv)) || !(sema = init_sem(args)))
        return 1;
    printf("here\n");
    if (!(philo = (t_philo *)malloc(sizeof(t_philo) * args->nb_philo)))
        return 1;
    i = 0;
    struct timeval time;
    gettimeofday(&time, NULL);
    while (i < args->nb_philo)
    {
        philo[i].args = args;
        philo[i].sema = sema;
        philo[i].index = i + 1;
        philo[i].alive = 1;
        philo[i].last_eat = (time.tv_sec *1000 - time.tv_usec / 1000);
        i++;
    }
    if (!(init_threads_living(philo)))
        return 1;
    if (!(init_threads_check(philo)))
        return 1;
    i = -1;
    while (++i < philo->args->nb_philo)
    {
        pthread_detach(philo[i].living);
        pthread_detach(philo[i].check);
    }
    free_all(philo);
    return 0;
}

int     free_all(t_philo *philo)
{
    int i;

    free(philo->args);
    pthread_mutex_destroy(&philo->sema->stdout);
    pthread_mutex_destroy(&philo->sema->forks[i]);
    i = -1;
    while (++i < philo->args->nb_philo)
        pthread_mutex_destroy(&philo->sema->sem_philo[i]);
    free(philo->sema->sem_philo);
    free(philo->sema);
    free(philo);
    return (0);
}

int init_threads_check(t_philo *philo)
{
    int i;
    i = 0;
    while (i < philo[0].args->nb_philo)
    {
        if(pthread_create(&philo[i].check, NULL, check, &philo[i]))
            return 0;
        i++;
    }
    i = -1;
    while (++i < philo[0].args->nb_philo)
        pthread_join(philo[i].check, NULL);
    i = -1;
    while (++i < philo[0].args->nb_philo)
    {
        pthread_join(philo[i].living, NULL);
    }
    return 1;
}

int init_threads_living(t_philo *philo)
{
   int i;
    i = 0;

    while (i < philo[0].args->nb_philo)
    {
        if(pthread_create(&philo[i].living, NULL, living, &philo[i]))
            return 0;
        i++;
    }
    return 1;
}

int     try_take_fork(t_philo *philo)
{
    struct timeval time;
    pthread_mutex_lock(&philo->sema->forks[philo->index]);
    print_state(philo, TAKE_FORK);
    pthread_mutex_lock(&philo->sema->forks[(philo->index + 1) % philo->args->nb_philo]);
    print_state(philo, TAKE_FORK);
    pthread_mutex_lock(&philo->sema->sem_philo[philo->index]);
    gettimeofday(&time, NULL);
    philo->last_eat = (time.tv_sec *1000 + time.tv_usec /1000);
    print_state(philo, EATING);
    usleep(philo->args->t_to_sleep * 1000);
    pthread_mutex_unlock(&philo->sema->sem_philo[philo->index]);
    pthread_mutex_unlock(&philo->sema->forks[philo->index]);
    pthread_mutex_unlock(&philo->sema->forks[(philo->index + 1) % philo->args->nb_philo]);
    return 1;
}

char    *get_status(state etat)
{
    if (etat == THINKING)
        return("thinking");
    else if (etat == SLEEPING)
        return ("sleeping");
    else if (etat == DIED)
        return ("died");
    else if (etat == TAKE_FORK)
        return ("has taken a fork");
    return ("eating");
}


