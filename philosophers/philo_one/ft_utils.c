/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bothilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 10:34:31 by bothilie          #+#    #+#             */
/*   Updated: 2020/02/06 11:35:17 by bothilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static unsigned int		ft_len(int nb)
{
	unsigned int len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char					*ft_itoa(int n)
{
	unsigned int	size;
	unsigned int	nb;
	unsigned int	sign;
	unsigned char	*tab;

	nb = (unsigned int)n;
	size = ft_len(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!(tab = (unsigned char*)malloc(size + 1)))
		return (NULL);
	nb = n < 0 ? n * -1 : n * 1;
	sign = n < 0 ? 1 : 0;
	while (size > sign)
	{
		tab[size - 1] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
	if (n < 0)
		tab[0] = '-';
	tab[ft_len(n)] = '\0';
	return ((char *)tab);
}

char	*ft_strdup(const char *s1)
{
	unsigned int		i;
	unsigned int		j;
	char				*str;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	str = (char *)malloc((1 + i) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (j < i)
	{
		str[j] = s1[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_atoi(const char *str)
{
	int				i;
	long			r;
	int				s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + str[i] - '0';
		i++;
	}
	return (r * s);
}
