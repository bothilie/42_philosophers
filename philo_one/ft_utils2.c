/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 11:39:06 by bothilie          #+#    #+#             */
/*   Updated: 2020/05/21 10:27:25 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int			ft_len(unsigned long nb)
{
	unsigned long len;

	len = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char				*ft_itoa(unsigned long n)
{
	unsigned int	size;
	unsigned int	i;
	char			*tab;

	size = ft_len(n);
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (!(tab = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (++i <= size)
	{
		tab[size - i] = (n % 10) + '0';
		n = n / 10;
	}
	tab[size] = '\0';
	return ((char *)tab);
}

unsigned long		get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int			free_all(t_global *gl, int ret)
{
	int i;

	i = -1;
	pthread_mutex_destroy(&gl->sema->stdout);
	pthread_mutex_destroy(&gl->sema->died);
	pthread_mutex_destroy(&gl->sema->take);
	pthread_mutex_destroy(&gl->sema->put);
	while (++i < gl->args->nb_philo)
		pthread_mutex_destroy(&gl->sema->sem_philo[i]);
	i = -1;
	while (++i < gl->args->nb_philo)
		pthread_mutex_destroy(&gl->sema->forks[i]);
	free(gl->sema->sem_philo);
	free(gl->sema->forks);
	//free(gl->args);
	free(gl->sema);
	free(gl->philo);
	return (ret);
}
