/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:38:40 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/29 13:29:51 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_sem		*init_sem(t_arg *args)
{
	int		i;
	t_sem	*lock;

	i = -1;
	if (!(lock = (t_sem*)malloc(sizeof(t_sem))))
		return (NULL);
	if (pthread_mutex_init(&lock->stdout, NULL) ||\
			pthread_mutex_init(&lock->died, NULL) ||\
			pthread_mutex_init(&lock->take, NULL) ||\
			pthread_mutex_init(&lock->put, NULL))
		return (NULL);
	if (!(lock->sem_philo = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)\
					* args->nb_philo)))
		return (NULL);
	if (!(lock->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)\
					* args->nb_philo)))
		return (NULL);
	while (++i < args->nb_philo)
	{
		if (pthread_mutex_init(&lock->sem_philo[i], NULL)\
				|| pthread_mutex_init(&lock->forks[i], NULL))
			return (NULL);
	}
	return (lock);
}
