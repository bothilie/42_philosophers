/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 11:08:10 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/06 11:35:14 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
#define PHILO_ONE_H
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#define number_of_philosopher 5

char	*ft_itoa(int n);
char	*ft_strdup(const char *s1);
void	display_stamp_ms(int i, char *s, int time);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *str);

#endif

