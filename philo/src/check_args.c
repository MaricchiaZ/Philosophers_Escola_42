/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:06:16 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/12 16:10:08 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Invalid number of arguments!\n", 2);
		ft_putstr_fd("Include: nbr_philo time_to_starve time_eating time_sleeping (nbr_of_meals - opitional).\n", 2);
		return (0);
	}
	while(argv[i])
	{
		if (!ft_str_isdigit(argv[i]))
		{
			ft_putstr_fd("Invalid type of arguments! Arguments must be numbers.\n", 2);
			return (0); // retornamos falso ou erro
		}
		if (!chek_str_int_positive(argv[i]))
		{
			ft_putstr_fd("Invalid arguments! Arguments must be numbers integers and positive.\n", 2);
			return (0);	// retornamos falso ou erro
		}
		i++;
	}
	return (1); // retornamos OK
}