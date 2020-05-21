/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 13:47:42 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 11:43:17 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"


static int			init_philos(t_global *gl)
{
	int i;

	gl->num_philo = gl->args->nb_philo;
	gl->alive = 1;
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

static int			init_odd(t_global *gl)
{
	int i;

	i = 1;
	while (i < gl->args->nb_philo)
	{
		if (pthread_create(&gl->philo[i].living, NULL, living, &gl->philo[i]))
			return (0);
		if (pthread_detach(gl->philo[i].living))
			return (0);
		if (pthread_create(&gl->philo[i].check, NULL, check, &gl->philo[i]))
			return (0);
		if (pthread_detach(gl->philo[i].check))
			return (0);
		i = i + 2;
	}
	return (1);
}

static int			init_even(t_global *gl)
{
	int i;

	i = 0;
	while (i < gl->args->nb_philo)
	{
		if (pthread_create(&gl->philo[i].living, NULL, living, &gl->philo[i]))
			return (0);
		if (pthread_detach(gl->philo[i].living))
			return (0);
		if (pthread_create(&gl->philo[i].check, NULL, check, &gl->philo[i]))
			return (0);
		if (pthread_detach(gl->philo[i].check))
			return (0);
		i = i + 2;
	}
	return (1);
}



int			main(int argc, char **argv)
{
	t_global	*gl;

	if (argc < 5 || argc > 6)
		return (print_error("Not good number of arguments\n"));
	gl = get_gl();
	if (!(gl->args = parse_args(argc, argv)))
		return (1);
	if (!(gl->sema = init_sem(gl->args)) || init_philos(gl)\
	|| !(init_even(gl)) || !(init_odd(gl)))
		return (1);
	while (1)
	{
		pthread_mutex_lock(&gl->sema->died);
		if (gl->alive == 0)
			return (free_all(gl, 1));
		pthread_mutex_unlock(&gl->sema->died);
		if (gl->num_philo == 0)
			break ;
		usleep(10);
	}
	write(1, "They all have eaten enough\n", 27);
	return (free_all(gl, 0));
}





