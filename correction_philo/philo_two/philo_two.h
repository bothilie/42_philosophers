/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:38:34 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/29 13:49:45 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <semaphore.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>

typedef enum {
	THINKING, EATING, HUNGRY, SLEEPING, DIED, TAKE_FORK
}	t_state;

typedef struct	s_args
{
	int		nb_philo;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		nb_eat;
}				t_arg;

typedef struct	s_sem
{
	sem_t			*stdout;
	sem_t			*died;
	sem_t			*take;
	sem_t			*put;
	sem_t			*forks;
	sem_t			*sem_philo;
}				t_sem;

typedef struct	s_philo
{
	int					index;
	unsigned long		last_eat;
	unsigned long		start;
	pthread_t			check;
	pthread_t			living;
	int					nb_eat;
}				t_philo;

typedef struct	s_global
{
	t_sem		*sema;
	t_arg		*args;
	t_philo		*philo;
	int			alive;
	int			num_philo;
}				t_global;

t_arg			*parse_args(int argc, char **argv);
int				ft_atoi(const char *str);
t_sem			*init_sem(t_arg *args);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *s1);
char			*get_status(t_state etat);
int				init_threads_living(t_global *global);
int				init_threads_check(t_global *global);
char			*ft_itoa(unsigned long n);
void			print_state(t_philo *philo, t_global *gl, t_state etat);
void			*living(void *arg);
void			*check(void *arg);
int				ft_isdigit(int c);
int				try_take_fork(t_philo *philo, t_global *global);
void			ft_exit_thread(t_philo *philo);
int				free_all(t_global *global);
t_global		*get_gl();
unsigned long	get_time();
int				init_even(t_global *gl);
int				init_odd(t_global *gl);
void			ft_sleeping(int n);
int				init_philos(t_global *gl);
int				print_error(char *str);
int				ft_unlink(int ret);

#endif
