/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 20:03:57 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 11:31:02 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// thread que verificará se os philos estão satisfeitos.

void	*alert_end_meals(void *arg)
{
	t_pd	*pdinner;
	int		i;

	pdinner = arg;
	i = 0;
	sem_wait(pdinner->msg); // aguardamos as "mensagens"
	while (i < pdinner->nbr_philo)
	{
		sem_post(pdinner->msg); //sem_post desbloqueia a seção crítica. Isso permite que outros processos acessem a seção crítica.
		sem_wait(pdinner->check_meals); // usamos para aguardar que a seção crítica "n de refeições" seja desbloqueada
		// sem_wait é um mecanismo de sincronização que bloqueia o processo atual até que o semáforo seja desbloqueado
		sem_wait(pdinner->msg); // para bloquear a seção crítica novamente.
		i++;
	}
	sem_post(pdinner->stop); //  para sinalizar que a verificação do número de refeições foi concluída.
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
