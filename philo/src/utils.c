/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:16:17 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 17:12:38 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	ft_str_isdigit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	chek_str_int_positive(const char *nptr)
{
	int			i;
	int			signal;
	long int	nb;

	i = 0;
	signal = 1;
	nb = 0;
	if (!nptr[i])
		return (0);
	while ((nptr[i] == '\t') || (nptr[i] == '\v') || (nptr[i] == '\f') || \
	(nptr[i] == '\n') || (nptr[i] == '\r') || (nptr[i] == ' '))
		i = i + 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i++] == '-')
			signal *= -1;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
		nb = (nb * 10) + (nptr[i++] - 48);
	nb = nb * signal;
	if (nb > INT_MAX && nb < 0)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signal;
	int	nb;

	i = 0;
	signal = 1;
	nb = 0;
	if (!nptr[i])
		return (0);
	while ((nptr[i] == '\t') || (nptr[i] == '\v') || (nptr[i] == '\f') || \
	(nptr[i] == '\n') || (nptr[i] == '\r') || (nptr[i] == ' '))
		i = i + 1;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signal *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	return (nb * signal);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	aux;
	void	*tab;
	int		i;

	if (nmemb == 0)
		return (NULL);
	if (nmemb > 2147483647 || size > 2147483647 || size * nmemb > 2147483647)
		return (NULL);
	aux = (size) * (nmemb);
	tab = malloc(aux);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (nmemb && tab)
	{
		*(unsigned char *)(tab + i) = '\0';
		i++;
		nmemb--;
	}
	return (tab);
}
