/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:09 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/29 13:50:27 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char		*get_status(t_state etat)
{
	if (etat == THINKING)
		return (" is thinking");
	else if (etat == SLEEPING)
		return (" is sleeping");
	else if (etat == DIED)
		return (" died");
	else if (etat == TAKE_FORK)
		return (" has taken a fork ");
	return (" is eating ");
}

void		print_state_2(t_philo *philo)
{
	char *index;

	index = ft_itoa(get_time() - philo->start);
	write(1, index, ft_strlen(index));
	free(index);
	index = ft_itoa(philo->index + 1);
	write(1, " philo ", 7);
	write(1, index, ft_strlen(index));
	free(index);
}

void		print_state(t_philo *philo, t_state etat)
{
	t_global	*gl;
	char		*index;

	gl = get_gl();
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
	print_state_2(philo);
	index = get_status(etat);
	write(1, index, ft_strlen(index));
	write(1, "\n", 1);
	if (sem_post(gl->sema->stdout) == -1)
		print_error("error : sem_post\n");
}

int			print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (2);
}
