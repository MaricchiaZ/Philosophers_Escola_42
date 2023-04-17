/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:32:59 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 13:20:47 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_sleep(time_t microsec, t_pd *pdinner)
{
	time_t	init;

	init = get_time();
	while (get_time() - init < microsec)
	{
		pthread_mutex_lock(&pdinner->msg);
		if (pdinner->stop == TRUE)
		{
			pthread_mutex_unlock(&pdinner->msg);
			break ;
		}
		pthread_mutex_unlock(&pdinner->msg);
		if (pdinner->nbr_philo < 100)
			usleep(100);
		else
			usleep(1000);
	}
}
