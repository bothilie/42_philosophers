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
        philo[i].nb_eat = 0;
        philo[i].last_eat = (time.tv_sec *1000 - time.tv_usec / 1000);
        i++;
    }
    if (!(init_threads_living(philo)))
            return 1;
    free_all(philo);
    return 0;
}

int     free_all(t_philo *philo)
{
    int i;

    sem_close(philo->sema->stdout);
    sem_close(philo->sema->forks);
    i = -1;
    while (++i < philo->args->nb_philo)
        sem_close(philo->sema->sem_philo[i]);
    free(philo->sema->sem_philo);
    free(philo->sema);
    free(philo->args);
    free(philo);
    return (0);
}


int init_threads_living(t_philo *philo)
{
   int i;
   int status;
   
   i = 0;
   while (i < philo[0].args->nb_philo)
    {
        if(!(philo[i].living = fork()))
            living(&philo[i]);
        i++;
    }
    status = 0;
    i = 0;
    if (waitpid(-1, &status, 0) <0 || WIFEXITED(status))
    {
        while (i < philo->args->nb_philo)
        {
            kill(philo[i].living, SIGINT);
            i++;
        }
    }
    return 1;
}

int     try_take_fork(t_philo *philo)
{
    struct timeval time;
    sem_wait(philo->sema->forks);
    print_state(philo, TAKE_FORK);
    sem_wait(philo->sema->forks);
    print_state(philo, TAKE_FORK);
    sem_wait(philo->sema->sem_philo[philo->index]);
    gettimeofday(&time, NULL);
    philo->last_eat = (time.tv_sec *1000 + time.tv_usec /1000);
    print_state(philo, EATING);
    usleep(philo->args->t_to_sleep * 1000);
    sem_post(philo->sema->sem_philo[philo->index]);
    sem_post(philo->sema->forks);
    sem_post(philo->sema->forks);
    return 1;
}




