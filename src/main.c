/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:49 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/11 07:59:39 by maclara-         ###   ########.fr       */
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
	if (!check_args(argc, argv))
		return(-1);
	if (init_)
	return (0);
}
