#include "philo_two.h"

int     print_state(t_philo *philo, state etat)
{
    
    struct timeval time;
    gettimeofday(&time, NULL);
    sem_wait(philo->sema->stdout);
    char *index;
    index = ft_itoa(time.tv_sec * 1000 + time.tv_usec / 1000);
    write(1, index, ft_strlen(index));
    free(index);
    index = ft_itoa(philo->index);
    write(1, " philo ", 7);
    write(1, index, ft_strlen(index));
    free(index);
    write(1, " is ", 4);
    char *str_etat = get_status(etat);
    write(1, str_etat, ft_strlen(str_etat));
    write(1, "\n", 1);
    sem_post(philo->sema->stdout);
    return 0;
}