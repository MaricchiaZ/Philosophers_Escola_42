/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:49 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/06 13:34:51 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_life()
{
	while(1)
	{
	eat();
	think();
	sleep();	
	}
}

int	main(int argc, char **argv) //nb_filo - t_morte - t_comer - t_dormir - qts_refei(opcional)
{
	
	return (0);
}
