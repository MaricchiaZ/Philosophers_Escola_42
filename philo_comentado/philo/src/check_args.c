/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:06:16 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/23 12:00:29 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv) // conferimos o número de args passados e se são numéricos, positivos e não estouram o INT_MAX
{
	int i;

	i = 1;
	if (argc < 5 || argc > 6) // só podemos ter 5 ou 6 argumentos, se for diferente disso
	{
		ft_putstr_fd("Invalid number of arguments!\n", 2); // avisamos que o número é inválido
		ft_putstr_fd("Include: nbr_philo time_to_starve time_eating time_sleeping (nbr_of_meals - opitional).\n", 2);
		// e orientamos como passar os argumentos
		return (0); // retornamos o 0 = false
	}
	while(argv[i]) // vamos olhar argumento por argumento, para ver se são numéricos, positivos e não estouram o INT_MAX
	{
		if (!ft_str_isdigit(argv[i])) // se não for composto por dígitos
		{
			ft_putstr_fd("Invalid type of arguments! Arguments must be numbers.\n", 2); // avisamos o erro
			return (0); // retornamos falso ou erro
		}
		if (!chek_str_int_positive(argv[i])) // aqui vemos se é positivo e se está no intervalo de 0 até o INT_MAX
		{
			ft_putstr_fd("Invalid arguments! Arguments must be numbers integers and positive.\n", 2); // avisamos o erro
			return (0);	// retornamos falso ou erro
		}
		i++; // olhamos todos os argumentos passados
	}
	return (1); // se estiver tudo em ordem, retornamos OK (1 = true)
}