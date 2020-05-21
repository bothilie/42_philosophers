/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:07 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 10:50:50 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void				ft_sleeping(int n)
{
	unsigned long start;
	unsigned long passed;

	start = get_time();
	while (1)
	{
		passed = get_time() - start;
		if (passed > n)
			break ;
		usleep(1);
	}
}

static int			try_take_fork(t_philo *philo, t_global *gl)
{
	if (sem_wait(gl->sema->take) == -1)
		print_error("error : sem_wait\n");
	if (sem_wait(gl->sema->forks) == -1)
		print_error("error : sem_wait\n");
	print_state(philo, TAKE_FORK);
	if (sem_wait(gl->sema->forks) == -1)
		print_error("error : sem_wait\n");
	print_state(philo, TAKE_FORK);
	if (sem_post(gl->sema->take) == -1)
		print_error("error : sem_post\n");
	if (sem_wait(gl->sema->sem_philo) == -1)
		print_error("error : sem_wait\n");
	philo->last_eat = get_time();
	if (sem_post(gl->sema->sem_philo) == -1)
		print_error("error : sem_post\n");
	print_state(philo, EATING);
	ft_sleeping(gl->args->t_to_sleep);
	if (sem_wait(gl->sema->put) == -1)
		print_error("error : sem_wait\n");
	if (sem_post(gl->sema->forks) == -1 || sem_post(gl->sema->forks) == -1)
		print_error("error : sem_post\n");
	if (sem_post(gl->sema->put) == -1)
		print_error("error : sem_post\n");
	return (1);
}

void		*living(void *arg)
{
	t_philo		*philo;
	t_global	*gl;

	philo = (t_philo*)arg;
	gl = get_gl();
	while (1)
	{
		print_state(philo, THINKING);
		try_take_fork(philo, gl);
		philo->nb_eat++;
		if (gl->args->nb_eat && philo->nb_eat >= gl->args->nb_eat)
			break ;
		print_state(philo, SLEEPING);
		ft_sleeping(gl->args->t_to_sleep);
	}
	gl->num_philo--;
	return (NULL);
}

void		*check(void *arg)
{
	t_philo		*philo;
	t_global	*gl;

	gl = get_gl();
	philo = (t_philo*)arg;
	while (1)
	{
		if (sem_wait(gl->sema->sem_philo) == -1)
			print_error("error : sem_wait\n");
		if (get_time() - philo->last_eat > (unsigned long)gl->args->t_to_die)
		{
			print_state(philo, DIED);
			if (sem_wait(gl->sema->died) == -1)
				print_error("error : sem_wait\n");
			gl->alive = 0;
			if (sem_post(gl->sema->died) == -1)
				print_error("error : sem_post\n");
			break ;
		}
		if (sem_post(gl->sema->sem_philo) == -1)
			print_error("error : sem_post\n");
		ft_sleeping(10);
	}
	return (NULL);
}



int			init_philos(t_global *gl)
{
	int i;

	gl->alive = 1;
	gl->num_philo = gl->args->nb_philo;
	if (!(gl->philo = (t_philo *)malloc(sizeof(t_philo) * gl->args->nb_philo)))
		return (1);
	i = -1;
	while (++i < gl->args->nb_philo)
	{
		gl->philo[i].index = i;
		gl->philo[i].nb_eat = 0;
		gl->philo[i].start = get_time();
		gl->philo[i].last_eat = get_time();
	}
	return (0);
}
