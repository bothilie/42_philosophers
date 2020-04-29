/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:05 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/28 12:20:05 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

sem_t		*init_mutex(int i, char *nom)
{
	sem_t	*dest;

	sem_unlink(nom);
	if (!(dest = sem_open(nom, O_CREAT, 0666, i)))
		return (NULL);
	return (dest);
}

t_sem		*init_sem(t_arg *args)
{
	t_sem	*lock;

	if (!(lock = (t_sem*)malloc(sizeof(t_sem))))
		return (NULL);
	if (!(lock->sem_philo = init_mutex(args->nb_philo, "philo")))
		return (NULL);
	if (!(lock->put = init_mutex(1, "put")))
		return (NULL);
	if (!(lock->take = init_mutex(1, "take")))
		return (NULL);
	if (!(lock->died = init_mutex(1, "died")))
		return (NULL);
	if (!(lock->stdout = init_mutex(1, "stdout")))
		return (NULL);
	if (!(lock->forks = init_mutex(args->nb_philo, "forks")))
		return (NULL);
	return (lock);
}
