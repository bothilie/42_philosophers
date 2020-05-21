/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:01 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 11:40:08 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int				init_philos(t_global *gl)
{
	int i;

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

int				ft_unlink(int ret)
{
	sem_unlink("stdout");
	sem_unlink("died");
	sem_unlink("sem_philo");
	sem_unlink("take");
	sem_unlink("put");
	sem_unlink("forks");
	return (ret);
}

int				free_all(t_global *gl)
{
	if (sem_close(gl->sema->stdout) == -1 || sem_close(gl->sema->died) == -1\
		|| sem_close(gl->sema->take) == -1 || sem_close(gl->sema->put) == -1\
	|| sem_close(gl->sema->forks) == -1 || sem_close(gl->sema->sem_philo) == -1)
		print_error("error : sem_close\n");
	free(gl->args);
	free(gl->sema);
	free(gl->philo);
	return (ft_unlink(0));
}

static int				init_threads_living(t_global *gl)
{
	int i;
	int status;

	init_even(gl);
	init_odd(gl);
	status = 0;
	i = 0;
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status) && (status == 512 || status == 768))
		{
			while (i++ < gl->args->nb_philo)
				kill(gl->philo[i].living, SIGINT);
			return (2);
		}
		else if (WIFEXITED(status) && status == 256)
		{
			gl->num_philo--;
			if (gl->num_philo == 0)
				return (1);
		}
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_global	*gl;
	int			ret;

	if (argc < 5 || argc > 6)
	{
		write(1, "Not good number of arguments\n", 29);
		return (1);
	}
	gl = get_gl();
	gl->alive = 1;
	if (!(gl->args = parse_args(argc, argv)))
		return (1);
	if (!(gl->sema = init_sem(gl->args)) || init_philos(gl))
		return (1);
	gl->num_philo = gl->args->nb_philo;
	if (!(ret = init_threads_living(gl)))
		return (1);
	if (ret == 2)
		return (ft_unlink(1));
	write(1, "They all have eaten enough\n", 27);
	return (free_all(gl));
}
