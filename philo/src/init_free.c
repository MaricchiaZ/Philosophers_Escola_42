/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:36:05 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 13:35:02 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_pd	*pdinner)
{
	int	i;

	i = 0;
	while (i < pdinner->nbr_philo)
	{
		pdinner->philo[i].stop = FALSE;
		pdinner->philo[i].nbr_meals = 0;
		pdinner->philo[i].id = i + 1;
		pdinner->philo[i].pdinner = pdinner;
		pdinner->philo[i].r_fork = &pdinner->fork[i];
		if (i == pdinner->nbr_philo - 1)
			pdinner->philo[i].l_fork = &pdinner->fork[0];
		else
			pdinner->philo[i].l_fork = &pdinner->fork[i + 1];
		i++;
	}
}

int	init_struct(t_pd *pdinner, char **argv)
{
	pdinner->stop = 0;
	pdinner->nbr_meals = 0;
	pdinner->nbr_philo = ft_atoi(argv[1]);
	pdinner->time_to_starv = ft_atoi(argv[2]);
	pdinner->time_eating = ft_atoi(argv[3]);
	pdinner->time_sleeping = ft_atoi(argv[4]);
	if (argv[5])
		pdinner->nbr_meals = ft_atoi(argv[5]);
	pdinner->philo = ft_calloc(pdinner->nbr_philo, sizeof(t_philo));
	pdinner->fork = ft_calloc(pdinner->nbr_philo, sizeof(pthread_mutex_t));
	if (!pdinner->philo || !pdinner->fork)
	{
		free(pdinner->philo);
		free(pdinner->fork);
		ft_putstr_fd("Malloc error...\n", 2);
		free(pdinner);
		return (0);
	}
	return (1);
}

int	init_mutex(t_pd *pdinner)
{
	int	i;

	i = 0;
	while (i < (int)pdinner->nbr_philo)
	{
		if (pthread_mutex_init(&pdinner->fork[i], NULL))
			break ;
		i++;
	}
	if (i-- != (int)pdinner->nbr_philo || \
	pthread_mutex_init(&pdinner->msg, NULL) || \
	pthread_mutex_init(&pdinner->mstop, NULL))
	{
		while (i >= 0)
			pthread_mutex_destroy(&pdinner->fork[i--]);
		ft_putstr_fd("Pthread error...\n", 2);
		free(pdinner->philo);
		free(pdinner->fork);
		free(pdinner);
		return (0);
	}
	return (1);
}

void	free_struct(t_pd *pdinner)
{
	int	i;

	i = 0;
	while (i < pdinner->nbr_philo)
	{
		if (pthread_join(pdinner->philo[i].thread, NULL))
			ft_putstr_fd("Pthread_join error...\n", 2);
		i++;
	}
	free(pdinner->philo);
	i = 0;
	while (i < pdinner->nbr_philo)
	{
		if (pthread_mutex_destroy(&pdinner->fork[i]))
			ft_putstr_fd("Pthread_mutex_destroy error...\n", 2);
		i++;
	}
	free(pdinner->fork);
	if (pthread_mutex_destroy(&pdinner->msg))
		ft_putstr_fd("Pthread_join error...\n", 2);
	if (pthread_mutex_destroy(&pdinner->mstop))
		ft_putstr_fd("Pthread_join error...\n", 2);
	free(pdinner);
}
