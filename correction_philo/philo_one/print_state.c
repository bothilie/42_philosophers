/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:38:45 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/29 13:46:10 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int			print_state(t_philo *philo, t_global *gl, t_state etat)
{
	char		*index;

	pthread_mutex_lock(&gl->sema->stdout);
	pthread_mutex_lock(&gl->sema->died);
	if (gl->alive == 0)
	{
		pthread_mutex_unlock(&gl->sema->died);
		return (1);
	}
	pthread_mutex_unlock(&gl->sema->died);
	index = ft_itoa(get_time() - philo->start);
	write(1, index, ft_strlen(index));
	free(index);
	index = ft_itoa(philo->index + 1);
	write(1, " philo ", 7);
	write(1, index, ft_strlen(index));
	free(index);
	index = get_status(etat);
	write(1, index, ft_strlen(index));
	write(1, "\n", 1);
	pthread_mutex_unlock(&gl->sema->stdout);
	return (0);
}

int			print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}
