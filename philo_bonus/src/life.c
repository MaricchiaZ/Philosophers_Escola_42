/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:41 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/16 14:11:03 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *life(t_pd *pdinner)
{
	pthread_mutex_lock(&philo->pdinner->time_meal); // travamos a variável tempo de refeição
	philo->last_meal = get_time(); // pegamos o tempo atual e
	pthread_mutex_unlock(&philo->pdinner->time_meal); // destravamos a variável tempo de refeição
	if (!(philo->id % 2)) // os philos de id par, vão dormir por uns milisegundos pra evitar concorrência
		usleep((philo->pdinner->time_eating - 10) * 1000);
	while ()
}

void	kill_philo(t_pd *pdinner)
{
	int	i;

	i = 0;
	while (i < pdinner->nbr_philo)
	{
		kill(pdinner->pid[i], SIGKILL);
		i++;
	}
}
