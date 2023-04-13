/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:18:48 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/13 15:21:01 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//man strcmp: 
// A função strcmp() compara os  bytes de s1 e s2.
// Ela retorna um inteiro menor que, igual a, ou maior que zero se s1 for encontrado, 
//respectivamente, menor que, igual a, ou maior que s2.

// essa função compara os bytes de s1 e s2 retorna a diferença em ASCII dos 
//valores encontrados em uma memsma posição de s1 e s2
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2) // enquanto s1 não chegar no byte nulo e
	// s1 e s2 forem idênticos
	{
		s1++; // avançamos o ponteiro de s1 para a próxima posição da string
		s2++; // avançamos o ponteiro de s2 para a próxima posição da string
	}
	return (*s1 - *s2); // se saiu do while, ou temos uma diferença e retornamos 
	// s1 menos s2, com o resultado sendo dado no intervalo da diferença em ASCII
	// OU s1 e acabou e até o fim elas eram iguais, nesse caso a diferença é zero
}
