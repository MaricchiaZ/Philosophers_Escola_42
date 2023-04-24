/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 08:29:11 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/24 07:57:10 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	wait_process(t_pd *pdinner) // faz o processo pai esperar a ação dos filósofos (processos filhos)
{
	t_philo	*aux; // auxiliar para percorrer os filósofos na lista ligada
	int		nbr_philo; //número de filósofos
	int		status; // variável necessária para o WEXITSTATUS

	nbr_philo = pdinner->nbr_philo + 1; // para poder decrementar
	status = 0;
	while (nbr_philo-- > 0 && WEXITSTATUS(status) == 0) //enquanto todos estiverem vivos
	{
		waitpid(-1, &status, 0); //o processo pai fica em espera
	}
	if (WEXITSTATUS(status) == 1) // se alguém morreu ou foi finalizado por que fez o número máximo de refeições
	{
		aux = pdinner->philo; // recebe o ponteiro para o primeiro filósofo
		nbr_philo = pdinner->nbr_philo + 1; // para poder decrementar no while
		while (nbr_philo-- > 0) // enquanto não passarmos por todos os filósofos
		{
			kill (aux->pid, SIGKILL); // finalizamos o processo do filósofo
			aux = aux->next; // vamos para o próximo
		}
	}	
}
