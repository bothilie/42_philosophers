#include "philo_one.h"

int main(int argc, char **argv)
{
    t_global    *gl;
    int         i;

    if (argc < 5 || argc > 6)
    {
        write(1, "Not good number of arguments\n", 29);
        return 1;
    }
    gl = get_gl();
    gl->alive = 1;
    if (!(gl->args = parse_args(argc, argv)) || !(gl->sema = init_sem(gl->args)))
        return 1;
    if (init_philos(gl)||!(init_even(gl)) || !(init_odd(gl)))
        return 1;
    while(1)
    {
        pthread_mutex_lock(&gl->sema->died);
        if (gl->alive == 0)
            return(free_all(gl));
        pthread_mutex_unlock(&gl->sema->died);  
    }
    free_all(gl);
    return 0;
}

int init_philos(t_global *gl)
{
    int i;

    if (!(gl->philo = (t_philo *)malloc(sizeof(t_philo) * gl->args->nb_philo)))
        return 1;
    i = -1;
    while (++i < gl->args->nb_philo)
    {
        gl->philo[i].index = i;
        gl->philo[i].start = get_time();
        gl->philo[i].last_eat = get_time();
    }
    return 0;
}

int     free_all(t_global *gl)
{
    int i;

    pthread_mutex_destroy(&gl->sema->stdout);
    pthread_mutex_destroy(&gl->sema->died);
    pthread_mutex_destroy(&gl->sema->take);
    pthread_mutex_destroy(&gl->sema->put);
    pthread_mutex_destroy(&gl->sema->forks[i]);
    i = -1;
    while (++i < gl->args->nb_philo)
        pthread_mutex_destroy(&gl->sema->sem_philo[i]);
    free(gl->sema->sem_philo);
    free(gl->args);
    free(gl->sema);
    return (0);
}

int init_odd(t_global *gl)
{
    int i;
    i = 1;
    while (i < gl->args->nb_philo)
    {
        if(pthread_create(&gl->philo[i].living, NULL, living, &gl->philo[i]))
            return 0;
        if (pthread_detach(gl->philo[i].living))
            return 0;
        if(pthread_create(&gl->philo[i].check, NULL, check, &gl->philo[i]))
            return 0;
        if (pthread_detach(gl->philo[i].check))
            return 0;
        i = i +2;
    }
    return 1;
}

int init_even(t_global *gl)
{
    int i;
    i = 0;
    while (i < gl->args->nb_philo)
    {
        if(pthread_create(&gl->philo[i].living, NULL, living, &gl->philo[i]))
            return 0;
        if (pthread_detach(gl->philo[i].living))
            return 0;
        if(pthread_create(&gl->philo[i].check, NULL, check, &gl->philo[i]))
            return 0;
        if (pthread_detach(gl->philo[i].check))
            return 0;
        i = i +2;
    }
    return 1;
}


