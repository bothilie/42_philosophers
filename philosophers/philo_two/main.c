/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:01 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/28 11:56:18 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			main(int argc, char **argv)
{
	t_global	*gl;

	if (argc < 5 || argc > 6)
		return (print_error("Not good number of arguments\n"));
	gl = get_gl();
	if (!(gl->args = parse_args(argc, argv)))
		return (1);
	if (!(gl->sema = init_sem(gl->args)))
		return (1);
	if (init_philos(gl) || !(init_even(gl)) || !(init_odd(gl)))
		return (1);
	while (1)
	{
		if (sem_wait(gl->sema->died) == -1)
			return (print_error("error : sem_wait\n"));
		if (gl->alive == 0)
			return (ft_unlink(1));
		if (sem_post(gl->sema->died) == -1)
			return (print_error("error : sem_post\n"));
		if (gl->num_philo == 0)
			break ;
	}
	write(1, "They all have eaten enough\n", 27);
	return (free_all(gl));
}

int			ft_unlink(int ret)
{
	sem_unlink("stdout");
	sem_unlink("died");
	sem_unlink("sem_philo");
	sem_unlink("take");
	sem_unlink("put");
	sem_unlink("forks");
	return (ret);
}

int			free_all(t_global *gl)
{
	if (sem_close(gl->sema->stdout) == -1 || sem_close(gl->sema->died) == -1 ||\
	sem_close(gl->sema->take) == -1 || sem_close(gl->sema->put) == -1 ||\
	sem_close(gl->sema->forks) == -1 || sem_close(gl->sema->sem_philo) == -1)
		print_error("error : sem_close\n");
	free(gl->args);
	free(gl->sema);
	free(gl->philo);
	return (ft_unlink(0));
}

int			init_odd(t_global *gl)
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

int			init_even(t_global *gl)
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
