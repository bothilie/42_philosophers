
#include "philo_two.h"

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
    gl->num_philo = gl->args->nb_philo;
    if (init_philos(gl)||!(init_even(gl)) || !(init_odd(gl)))
        return 1;
    while(1)
    {
        sem_wait(gl->sema->died);
        if (gl->alive == 0)
            return(ft_unlink(1));
        sem_post(gl->sema->died);
        if (gl->num_philo == 0)
            break;
    }
    write(1, "They all have eaten enough\n", 27);
    return free_all(gl);
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
        gl->philo[i].nb_eat = 0;
        gl->philo[i].start = get_time();
        gl->philo[i].last_eat = get_time();
    }
    return 0;
}

int ft_unlink(int ret)
{
    sem_unlink("stdout");
    sem_unlink("died");
    sem_unlink("sem_philo");
    sem_unlink("take");
    sem_unlink("put");
    sem_unlink("forks");
    return ret;
}

int     free_all(t_global *gl)
{
    sem_close(gl->sema->stdout);
    sem_close(gl->sema->died);
    sem_close(gl->sema->take);
    sem_close(gl->sema->put);
    sem_close(gl->sema->forks);
    sem_close(gl->sema->sem_philo);
    free(gl->args);
    free(gl->sema);
    free(gl->philo);
    return (ft_unlink(0));
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


