#ifndef PHILO_TWO_H
#define PHILO_TWO_H

#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef enum {
    THINKING, EATING, HUNGRY, SLEEPING, DIED, TAKE_FORK
}   state;

typedef struct  s_args
{
    int     nb_philo;
    int     t_to_die;
    int       t_to_eat;
    int     t_to_sleep;
    int     nb_eat;
}               t_arg;


typedef struct  s_sem
{
    sem_t       *stdout;
    sem_t       *forks;
    sem_t       **sem_philo;
}               t_sem;

typedef struct  s_philo
{
    int         index;
    t_sem       *sema;
    t_arg       *args;
    int         last_eat;
    int         alive;
    pthread_t   check;
    pthread_t   living;
    int         nb_eat;
}               t_philo;

t_arg       *parse_args(int argc, char **argv);
int         ft_atoi(const char *str);
t_sem       *init_sem(t_arg *args);
char        *ft_strjoin(char const *s1, char const *s2);
size_t      ft_strlen(const char *str);
char        *ft_strdup(const char *s1);
char        *get_status(state etat);
int         init_threads_living(t_philo *philo);
int         init_threads_check(t_philo *philo);
char        *ft_itoa(int n);
int         print_state(t_philo *philo, state etat);
void        *living(void *arg);
void        *check(void *arg);
int         ft_isdigit(int c);
int         try_take_fork(t_philo *philo);
void        ft_exit_thread(t_philo *philo);
int         free_all(t_philo *philo);
t_philo    *init_philo(t_philo *philo, t_sem *sema, t_arg *args);

#endif