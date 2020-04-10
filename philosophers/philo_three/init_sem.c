#include "philo_two.h"

sem_t   *open_sem(t_arg *args, int i, char *nom, int number)
{
    char *tmp;
    char *name;
    sem_t *dest;
    tmp = ft_itoa(i);
    name = ft_strjoin(nom, tmp);
    sem_unlink(name);
    if (!(dest = sem_open(name, O_CREAT, 0666, number)))
        return NULL;
    free(name);
    free(tmp);
    return dest;
}

t_sem *init_sem(t_arg *args) // Protéger les sema open
{
    int i;
    i = -1;
    t_sem   *sem;
    if (!(sem = (t_sem *)malloc(sizeof(t_sem))))
        return NULL;
    if (!(sem->stdout = open_sem(args, 1, "stdout", 1)))
        return NULL;
    if (!(sem->sem_philo = (sem_t **)malloc(sizeof(sem_t) * args->nb_philo)))
        return NULL;
    if (!(sem->forks = open_sem(args, 1, "fork", 5)))
        return NULL;
    while (++i < args->nb_philo)
    {
        if (!(sem->sem_philo[i] = open_sem(args, i, "philo", 1)))
            return NULL;
    }
    return sem;
}