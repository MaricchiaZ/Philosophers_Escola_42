/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:29:27 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 17:37:10 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *) malloc (sizeof (char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i] != '\0')
		dest[len++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		dest[len++] = s2[i++];
	dest[len] = '\0';
	return (dest);
}

static void	*str_complete(char *str, int ten, long int cpy_n, int i)
{
	while (ten >= 1)
	{
	str[i] = '0' + (cpy_n / ten);
	cpy_n = cpy_n - (cpy_n / ten) * ten;
	ten = ten / 10;
	i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int			signal_loc;
	int			ten;
	char		*str;
	int			i;
	long int	cpy_n;

	signal_loc = 0;
	ten = 1;
	i = 1;
	cpy_n = n;
	if (cpy_n < 0)
	{
		signal_loc = 1;
		cpy_n = cpy_n * -1;
	}
	while (ten <= cpy_n / 10)
	{
		ten = ten * 10;
		i++;
	}
	str = (char *) malloc(sizeof(char) * (i + signal_loc + 1));
	if (signal_loc == 1)
		str[0] = '-';
	str_complete(str, ten, cpy_n, signal_loc);
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
