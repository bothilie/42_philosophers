#include "philo_two.h"

sem_t   *init_mutex(int i, char *nom)
{
    char *tmp;
    char *name;
    sem_t *dest;

    sem_unlink(nom);
    if (!(dest = sem_open(nom, O_CREAT, 0666, i)))
        return NULL;
    free(nom);
    return dest;
}

t_sem *init_sem(t_arg *args) // Protéger les sema open
{
    int i;
    t_sem *lock;

    i = -1;
    if (!(lock = (t_sem*)malloc(sizeof(t_sem))))
        return NULL;
    lock->stdout = init_mutex(1, ft_strdup("stdout"));
    lock->forks = init_mutex(5, ft_strdup("forks"));
    lock->sem_philo = init_mutex(5, ft_strdup("philo"));
    lock->put = init_mutex(1, ft_strdup("put"));
    lock->take = init_mutex(1, ft_strdup("take"));
    lock->died = init_mutex(1, ft_strdup("died"));
    return lock;
}