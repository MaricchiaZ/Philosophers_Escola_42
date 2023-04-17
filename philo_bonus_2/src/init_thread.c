/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:03:57 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 17:34:24 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*alert_end_meals(void *arg)
{
	t_pd	*pdinner;
	int		i;

	pdinner = arg;
	i = 0;
	sem_wait(pdinner->msg);
	while (i < pdinner->nbr_philo)
	{
		sem_post(pdinner->msg);
		sem_wait(pdinner->check_meals);
		sem_wait(pdinner->msg);
		i++;
	}
	sem_post(pdinner->stop);
	return (NULL);
}

int	init_thread(t_pd *pdinner)
{
	if (pdinner->nbr_meals)
	{
		if (pthread_create(&pdinner->check, NULL, &alert_end_meals, pdinner))
		{
			ft_putstr_fd("Pthread_create error...\n", 2);
			return (0);
		}
		(pthread_detach(pdinner->check));
	}
	return (1);
}
