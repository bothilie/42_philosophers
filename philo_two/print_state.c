/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:09 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 10:52:48 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static char		*get_status(t_state etat)
{
	if (etat == THINKING)
		return (ft_strdup(" is thinking\n"));
	else if (etat == SLEEPING)
		return (ft_strdup(" is sleeping\n"));
	else if (etat == DIED)
		return (ft_strdup(" died\n"));
	else if (etat == TAKE_FORK)
		return (ft_strdup(" has taken a fork\n"));
	return ft_strdup((" is eating\n"));
}

void		print_state(t_philo *philo, t_state etat)
{
	t_global	*gl;
	char		*index;
	char		*time;
	char 		*status;
	char		*str;
	char 		*tmp;
	char 		*ph;

	gl = get_gl();
	status = get_status(etat);
	time = ft_itoa(get_time() - philo->start);
	ph = " philo ";
	index = ft_itoa(philo->index + 1);
	tmp = ft_strjoin(time, ph);
	str = ft_strjoin(tmp, index);
	free (tmp);
	tmp = ft_strjoin(str, status);
	if (sem_wait(gl->sema->stdout) == -1)
		print_error("error : sem_wait\n");
	if (sem_wait(gl->sema->died) == -1)
		print_error("error : sem_wait\n");
	if (gl->alive == 0)
	{
		if (sem_post(gl->sema->died) == -1)
			print_error("error : sem_post\n");
		return ;
	}
	if (sem_post(gl->sema->died) == -1)
		print_error("error : sem_post\n");
	write(1, tmp, ft_strlen(tmp));
	if (sem_post(gl->sema->stdout) == -1)
		print_error("error : sem_post\n");
	 free(time);
	free(index);
	free(status);
	free(tmp);
	free(str);
}

int			print_error(char *str)
{
	t_global *gl;

	gl = get_gl();
	write(2, str, ft_strlen(str));
	return (2);
}
