/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:07 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/28 11:56:08 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		*living(void *arg)
{
	t_philo		*philo;
	t_global	*gl;

	philo = (t_philo*)arg;
	gl = get_gl();
	while (1)
	{
		print_state(philo, gl, THINKING);
		try_take_fork(philo, gl);
		philo->nb_eat++;
		if (gl->args->nb_eat && philo->nb_eat >= gl->args->nb_eat)
			break ;
		print_state(philo, gl, SLEEPING);
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
			print_state(philo, gl, DIED);
			if (sem_wait(gl->sema->died) == -1)
				print_error("error : sem_wait\n");
			gl->alive = 0;
			if (sem_post(gl->sema->died) == -1)
				print_error("error : sem_post\n");
		}
		if (sem_post(gl->sema->sem_philo) == -1)
			print_error("error : sem_post\n");
		ft_sleeping(10);
	}
	return (NULL);
}

int			try_take_fork(t_philo *philo, t_global *gl)
{
	if (sem_wait(gl->sema->take) == -1)
		print_error("error : sem_wait\n");
	if (sem_wait(gl->sema->forks) == -1)
		print_error("error : sem_wait\n");
	print_state(philo, gl, TAKE_FORK);
	if (sem_wait(gl->sema->forks) == -1)
		print_error("error : sem_wait\n");
	print_state(philo, gl, TAKE_FORK);
	if (sem_post(gl->sema->take) == -1)
		print_error("error : sem_post\n");
	if (sem_wait(gl->sema->sem_philo) == -1)
		print_error("error : sem_wait\n");
	philo->last_eat = get_time();
	if (sem_post(gl->sema->sem_philo) == -1)
		print_error("error : sem_post\n");
	print_state(philo, gl, EATING);
	ft_sleeping(gl->args->t_to_eat);
	if (sem_wait(gl->sema->put) == -1)
		print_error("error : sem_wait\n");
	if (sem_post(gl->sema->forks) == -1 || sem_post(gl->sema->forks) == -1)
		print_error("error : sem_post\n");
	if (sem_post(gl->sema->put) == -1)
		print_error("error : sem_post\n");
	return (1);
}

int			init_philos(t_global *gl)
{
	gl->alive = 1;
	gl->num_philo = gl->args->nb_philo;
	if (!(gl->philo = (t_philo *)malloc(sizeof(t_philo) * gl->args->nb_philo)))
		return (1);
	return (0);
}
