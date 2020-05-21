/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:38:45 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 10:37:30 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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


int			print_state(t_philo *philo, t_state etat)
{
	t_global	*gl;
	char		*str;
	char 		*status;

	status = get_status(etat);
	gl = get_gl();
	str = get_str(philo, status);
	pthread_mutex_lock(&gl->sema->died);
	if (gl->alive == 0)
	{
		pthread_mutex_unlock(&gl->sema->died);
		free(str);
		return (1);
	}
	pthread_mutex_unlock(&gl->sema->died);
	write(1, str, ft_strlen(str));
	if (gl->alive)
		pthread_mutex_unlock(&gl->sema->stdout);
	free(str);
	return (0);
}


int			print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (1);
}

t_global		*get_gl(void)
{
	static t_global gl;

	return (&gl);
}