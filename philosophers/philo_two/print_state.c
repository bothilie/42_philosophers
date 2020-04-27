#include "philo_two.h"

char    *get_status(state etat)
{
    if (etat == THINKING)
        return(" is thinking");
    else if (etat == SLEEPING)
        return (" is sleeping");
    else if (etat == DIED)
        return ("died");
    else if (etat == TAKE_FORK)
        return (" has taken a fork ");
    return (" is eating ");
}

int     print_state(t_philo *philo, state etat)
{ 
    t_global *gl;
    
    gl = get_gl();
    sem_wait(gl->sema->stdout);
    sem_wait(gl->sema->died);
    if (gl->alive == 0)
    {
        sem_post(gl->sema->died);
        return 1;
    }
    sem_post(gl->sema->died);
    char *index;
    index = ft_itoa(get_time() - philo->start);
    write(1, index, ft_strlen(index));
    free(index);
    index = ft_itoa(philo->index + 1);
    write(1, " philo ", 7);
    write(1, index, ft_strlen(index));
    free(index);
    char *str_etat = get_status(etat);
    write(1, str_etat, ft_strlen(str_etat));
    write(1, "\n", 1);
    sem_post(gl->sema->stdout);
    return 0;
}