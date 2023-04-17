/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:32:59 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/12 16:36:32 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	to_sleep(time_t microsec, t_pd  *pdinner) //
{
	time_t	init; //tempo agora

	init = get_time(); //recebe o tempo agora 
	while (get_time() - init < microsec) //enquanto n atingir os microseg
	{
		pthread_mutex_lock(&pdinner->msg); // travamos o uso das mensagens
		if (pdinner->stop == TRUE) // se tiver um aviso pra parar
		{
			pthread_mutex_unlock(&pdinner->msg); // destravamos o uso das mensagens IIISIISIISISISISISIOIO
			break ; // saímos do while
		}
		pthread_mutex_unlock(&pdinner->msg); //destravamos o uso das mensagens )SPOSIPOAIOPIDAOPIOPADIOPIPAIP
		if (pdinner->nbr_philo < 100) // se o número de filósofos for menor do que 100
			usleep(100); // dormem por 100 microseg
		else // se for de 100 ou mais
			usleep(1000); // dormem por 1000 microseg
	}
}
