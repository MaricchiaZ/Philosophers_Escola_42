/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:06:16 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/11 07:50:17 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5 && argc > 6)
	{
		ft_putstr_fd("Invalid number of arguments!", 2);
		ft_putstr_fd("Include nbr_philo time_to_starve time_eating time_sleeping (nbr_of_meals - opitional)", 2);
		return (0)
	}
	while(argv[i])
	{
		if (!ft_str_isdigit(argv[i]))
		{
			ft_putstr_fd("Invalid type of arguments! Arguments must be numbers", 2);
			return (0);
		}
		if (ft_atoi_int_positive == -1)
		{
			ft_putstr_fd("Invalid arguments! Arguments must be numbers integers and positive", 2);
			return (0);			
		}
		i++;
	}
	return (1);
}