/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <bothilie@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 15:39:19 by bothilie          #+#    #+#             */
/*   Updated: 2020/04/29 13:45:32 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_arg		*get_args(t_arg *args, char **argv, int argc)
{
	args->nb_philo = ft_atoi(argv[1]);
	args->t_to_die = ft_atoi(argv[2]);
	args->t_to_eat = ft_atoi(argv[3]);
	args->t_to_eat = ft_atoi(argv[3]);
	args->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_eat = ft_atoi(argv[5]);
	else
		args->nb_eat = 0;
	return (args);
}

t_arg		*parse_args(int argc, char **argv)
{
	t_arg	*args;
	int		i;
	int		j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				print_error("error: args not valid\n");
				return (NULL);
			}
			j++;
		}
	}
	if (!(args = (t_arg *)malloc(sizeof(t_arg))))
		return (0);
	args = get_args(args, argv, argc);
	return (args);
}
