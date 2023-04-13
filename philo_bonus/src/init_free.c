/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:09:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/13 11:36:26 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_pdinner *pdinner)
{
	sem_unlink("fork")
	pdinner->
}

int	init_struct(t_pdinner *pdinner, char **argv)
{
	pdinner->nbr_philo = ft_atoi(argv[1]);
	pdinner->time_starv = ft_atoi(argv[2]);
	pdinner->time_eating = ft_atoi(argv[3]);
	pdinner->time_sleeping = ft_atoi(argv[4]);
	if (argv[5])
		pdinner->nbr_meals = ft_atoi(argv[5]);
	pdinner->philo->smby_died = 0;
	pdinner->init = 0;
	init_semaphores(pdinner);
	while (i < pdinner->nbr_philo)
	{
		pdinner->philo[i].id = i + 1;
		pdinner->philo[i].dying = 0;
		pdinner->philo[i].nbr_meals = 0;
	}
	return (1);			
}
