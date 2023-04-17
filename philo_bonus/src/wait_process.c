/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:29:11 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 09:30:37 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_process(t_pd *pdinner)
{
	t_philo	*aux;
	int		nbr_philo;
	int		status;

	nbr_philo = pdinner->nbr_philo + 1;
	status = 0;
	while (nbr_philo-- > 0 && WEXITSTATUS(status) == 0)
	{
		waitpid(-1, &status, 0);
	}
	if (WEXITSTATUS(status) == 1)
	{
		aux = pdinner->philo;
		nbr_philo = pdinner->nbr_philo + 1;
		while (nbr_philo-- > 0)
		{
			kill (aux->pid, SIGKILL);
			aux = aux->next;
		}
	}	
}
