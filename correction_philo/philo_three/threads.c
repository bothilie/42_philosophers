/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:07 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/28 12:32:48 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			*living(t_philo *arg)
{
	t_philo		*philo;
	t_global	*gl;

	gl = get_gl();
	philo = (t_philo*)arg;
	if (pthread_create(&philo->check, NULL, check, philo))
		exit(0);
	if (pthread_detach(philo->check))
		exit(0);
	while (1)
	{
		print_state(philo, gl, THINKING);
		try_take_fork(philo, gl);
		philo->nb_eat++;
		if (philo->nb_eat >= gl->args->nb_eat && gl->args->nb_eat)
			exit(1);
		print_state(philo, gl, SLEEPING);
		usleep(1000 * gl->args->t_to_sleep);
	}
}

void			*check(void *arg)
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
			exit(2);
		}
		if (sem_post(gl->sema->sem_philo) == -1)
			print_error("error : sem_post\n");
		ft_sleeping(5);
	}
}

int				try_take_fork(t_philo *philo, t_global *gl)
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

int				init_even(t_global *gl)
{
	int i;

	i = 0;
	while (i < gl->args->nb_philo)
	{
		gl->philo[i].start = get_time();
		gl->philo[i].last_eat = get_time();
		if (!(gl->philo[i].living = fork()))
			living(&gl->philo[i]);
		i = i + 2;
	}
	return (0);
}

int				init_odd(t_global *gl)
{
	int i;

	i = 1;
	while (i < gl->args->nb_philo)
	{
		gl->philo[i].start = get_time();
		gl->philo[i].last_eat = get_time();
		if (!(gl->philo[i].living = fork()))
			living(&gl->philo[i]);
		i = i + 2;
	}
	return (0);
}
