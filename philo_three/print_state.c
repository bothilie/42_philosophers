/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:09 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 11:24:35 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static char		*get_status(t_state etat)
{
	if (etat == THINKING)
		return (ft_strdup(" is thinking\n"));
	else if (etat == SLEEPING)
		return (ft_strdup(" is sleeping\n"));
	else if (etat == DIED)
		return (ft_strdup(" died"));
	else if (etat == TAKE_FORK)
		return (ft_strdup(" has taken a fork\n"));
	return ft_strdup((" is eating\n"));
}

static char		*get_str(t_philo *philo, char *status)
{
	char		*index;
	char		*time;
	char		*str;
	char 		*tmp;
	char 		*ph;

	
	time = ft_itoa(get_time() - philo->start);
	ph = " philo ";
	index = ft_itoa(philo->index + 1);
	tmp = ft_strjoin(time, ph);
	str = ft_strjoin(tmp, index);
	free (tmp);
	tmp = ft_strjoin(str, status);
			 free(time);
		free(index);
		free(status);
	return tmp;
}

void		print_state(t_philo *philo, t_state etat)
{
	t_global	*gl;
	char		*str;
	char		*status;


	gl = get_gl();
	status = get_status(etat);
	str = get_str(philo, status);
	if (sem_wait(gl->sema->stdout) == -1)
		print_error("error : sem_wait\n");
	if (sem_wait(gl->sema->died) == -1)
		print_error("error : sem_wait\n");
	if (gl->alive == 0)
	{
		free(str);
		if (sem_post(gl->sema->died) == -1)
			print_error("error : sem_post\n");
		return ;
	}
	if (sem_post(gl->sema->died) == -1)
	print_error("error : sem_post\n");
	write(1, str, ft_strlen(str));
	if (DIED != etat)
	{
	if (sem_post(gl->sema->stdout) == -1)
		print_error("error : sem_post\n");
	}
	free(str);
}

void			print_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(3);
}
