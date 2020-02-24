/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:52:38 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/06 11:35:09 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>
#include <sys/time.h>

/// Ordre exact ?
/// modifier printf avec write > PB thread
/// memset
/// verifier retour pour detach ? ou general ?
/// affichage mort < 10 ms mort
/// pas de variables globales : lock
/// DEFINE arguments
/// Interval negatif parfois entre start avant et end 

//int counter;
pthread_mutex_t lock[5];
void	*philosophe_1(void *arg);
void	*philosophe_2(void *arg);
void	*philosophe_3(void *arg);
void	*philosophe_4(void *arg);
void	*philosophe_5(void *arg);
//int number_of_philosopher = 5;
int time_to_die  = 900000;
int time_to_sleep = 200000;
int time_to_eat = 150000; // a voir avec process avant
int number_of_time_each_philosophers_must_eat = 10;


int main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		write(1, "Wrong number of arguments\n", 26);
//	int number_of_philosopher = ft_atoi(argv[1]);
//	int time_to_die  = argv[2];
//	int time_to_sleep = argv[3];
//	int time_to_eat = argv[4]; // a voir avec process avant
//	if (argc == 6)
//		int number_of_time_each_philosophers_must_eat = argv[5];
//	pthread_mutex_t lock;
	argv[1] = "";
	void *philosophes[number_of_philosopher];

	pthread_t philo[number_of_philosopher];
	int i;
	i = 0;
	if (pthread_mutex_init(lock, NULL) != 0)
	{
		write(1, "Erreur in mutex init\n", 21);
	}
	while ( i < number_of_philosopher)
	{
		if (pthread_create(&philo[i], NULL, &philosophe_5, &philosophes[i]))
			write(1, "Can't read the thread\n", 22);
		i++;
	}
	i = 0;
	while(i < number_of_philosopher)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	pthread_mutex_destroy(lock);
	return(0);
}

void	*philosophe_5(void *arg)
{
	int eat = 0;
	int i;
	i = (long long)arg % 5 + 1;
	int interval;
	char *nb = ft_itoa(i);
	struct timeval time, start, end;
	while (eat < number_of_time_each_philosophers_must_eat)
	{
		gettimeofday(&end, NULL);
		interval = (end.tv_usec - start.tv_usec) / 1000;
		printf("interval %s : %d\n", nb, interval);
		if (interval > time_to_die)
		{
			printf("====>>>>philo %d is dead\n", i);
			free(nb);
			return("DEAD");
		}
		gettimeofday(&start, NULL);
		pthread_mutex_lock(&lock[i - 1]);
		//display_stamp_ms(i, " has taken a fork\n", start.tv_usec);
		printf("%d, Philo %s has taken a fork\n", start.tv_usec, nb);
		pthread_mutex_lock(&lock[i]);
		//display_stamp_ms(i, " has taken a fork\n", start.tv_usec);
		printf("%d, Philo %s has taken a fork\n", start.tv_usec, nb);
		gettimeofday(&start, NULL);
		//display_stamp_ms(i, " is eating\n", start.tv_usec);
		printf("%d, Philo %s is eating\n", start.tv_usec, nb);
		usleep(time_to_eat);
		eat++;
		pthread_mutex_unlock(&lock[i - 1]);
		pthread_mutex_unlock(&lock[i]);
		gettimeofday(&time, NULL);
		//display_stamp_ms(i, " is sleeping\n", start.tv_usec);
		printf("%d, Philo %s is sleeping\n", time.tv_usec, nb);
		usleep(time_to_sleep);
		gettimeofday(&time, NULL);
		//display_stamp_ms(i, " is thinking\n", start.tv_usec);
		printf("%d, Philo %s is thinking\n", time.tv_usec, nb);
	}
	free(nb);
	return(NULL);
}

void	display_stamp_ms(int i, char *s, int time)
{
	char *nb;
	char *time_str;

	time = time / 1000;
	nb = ft_itoa(i);
	time_str = ft_itoa(time);
	write(1, time_str, ft_strlen(time_str));
	write(1, ", Philo ", ft_strlen("Philo "));
	write(1, nb, ft_strlen(nb));
	write(1, s, ft_strlen(s));
	free(nb);
	free(time_str);
	nb = NULL;
	time_str = NULL;
}































void	*philosophe_1(void *arg)
{
	arg = "merci";
	int a = 1;
	int eat;
	eat = 0;
	struct timeval time, start, end;
	gettimeofday(&start, 0);
	int interval;
	while (eat < number_of_time_each_philosophers_must_eat)
	{
		gettimeofday(&end, NULL);
		interval = end.tv_usec - start.tv_usec;
		printf("interval: %d\n", interval);
		if (interval > time_to_die)
		{
			printf("====>>>>philo %d is dead\n", a);
			return(NULL);
		}
		gettimeofday(&start, NULL);
		pthread_mutex_lock(&lock[0]);
		printf("%d, Philo %d has taken a fork\n", start.tv_usec, a);
		pthread_mutex_lock(&lock[1]);
		printf("%d, Philo %d has taken a fork\n", start.tv_usec, a);
		printf("%d, Philo %d is eating\n", start.tv_usec, a);
		usleep(time_to_eat);
		eat++;
		pthread_mutex_unlock(&lock[0]);
		pthread_mutex_unlock(&lock[1]);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is sleeping\n", time.tv_usec, a);
		usleep(time_to_sleep);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is thinking\n", time.tv_usec, a);
	}
	return(NULL);
}

void	*philosophe_2(void *arg)
{
	int a = 2;
	int eat;
	eat = 0;
	int interval;
	struct timeval time, start, end;
	while (eat < number_of_time_each_philosophers_must_eat)
	{
		arg = "merci";
		gettimeofday(&end, NULL);
		interval = end.tv_usec - start.tv_usec;
		if (interval > time_to_die)
		{
			printf("====>>>>philo %d is dead\n", a);
			return(NULL);
		}
		gettimeofday(&start, NULL);
		printf("%d, Philo %d is eating\n", start.tv_usec, a);
		pthread_mutex_lock(&lock[1]);
		pthread_mutex_lock(&lock[2]);
		usleep(time_to_eat);
		eat++;
		pthread_mutex_unlock(&lock[1]);
		pthread_mutex_unlock(&lock[2]);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is sleeping\n", time.tv_usec, a);
		usleep(time_to_sleep);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is thinking\n", time.tv_usec, a);
	}
	return(NULL);
}

void	*philosophe_3(void *arg)
{
	int a;
	a = 3;
	int eat;
	eat = 0;
	int interval;
	struct timeval time, start, end;
	while (eat < number_of_time_each_philosophers_must_eat)
	{
		arg = "merci";
		gettimeofday(&end, NULL);
		interval = end.tv_usec - start.tv_usec;
		printf("interval: %d\n", interval);
		if (interval > time_to_die)
		{
			printf("====>>>>philo %d is dead\n", a);
			return(NULL);
		}
		gettimeofday(&start, NULL);
		printf("%d, Philo %d is eating\n", start.tv_usec, a);
		pthread_mutex_lock(&lock[3]);
		pthread_mutex_lock(&lock[2]);
		usleep(time_to_eat);
		eat++;
		pthread_mutex_unlock(&lock[2]);
		pthread_mutex_unlock(&lock[3]);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is sleeping\n", time.tv_usec, a);
		usleep(time_to_sleep);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is thinking\n", time.tv_usec, a);
	}
	return(NULL);
}

void	*philosophe_4(void *arg)
{
	int a = 4;
	int eat;
	eat = 0;
	int interval;
	struct timeval time, start, end;
	while (eat < number_of_time_each_philosophers_must_eat)
	{
		arg = "merci";
		gettimeofday(&end, NULL);
		interval = end.tv_usec - start.tv_usec;
		printf("interval: %d\n", interval);
		if (interval > time_to_die)
		{
			printf("====>>>>philo %d is dead\n", a);
			return(NULL);
		}
		gettimeofday(&start, NULL);
		printf("%d, Philo %d is eating\n", start.tv_usec, a);
		pthread_mutex_lock(&lock[3]);
		pthread_mutex_lock(&lock[4]);
		usleep(time_to_eat);
		eat++;
		pthread_mutex_unlock(&lock[4]);
		pthread_mutex_unlock(&lock[3]);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is sleeping\n", time.tv_usec, a);
		usleep(time_to_sleep);
		gettimeofday(&time, NULL);
		printf("%d, Philo %d is thinking\n", time.tv_usec, a);
	}
	return(NULL);
}

