/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:16:17 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/11 07:56:30 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//descrição da função nas diretrizes da tarefa:
//Produz a string 's' para o descritor de arquivo dado.

void	ft_putstr_fd(char *s, int fd)
{
	int	i; // criamos um índice para percorrer a string.

	i = 0; // o índice se inicia zerado
	while (s[i] != '\0') // enquanto o conteúdo de s[i] for diferente de nulo
	{
		write (fd, &s[i], 1); // descritor de arquivo dad colocamos o  conteúdo de s[i]
		i++; // i ganha uma unidade
	}
}

int	ft_str_isdigit(char *str) // confere se a string é compsta só por dígitos
{
	while (*str) // enquanto tiver coisa na string
	{
		if (!('0' <= *str && *str <= '9')) // se for diferente de 0 a 9
			return (0); // retorna erro // 0 = false
		str++; // avançamos na string
	}
	return (1); // retornamos 1 quando acabou a string e só tinha números nela
}

//esta função tranforma uma string de char numérico em um inteiro e confere se é um inteiro positivo e não
// maior do que o INT_MAX
int	ft_atoi_int_positive(const char *nptr)
{
	int	i; // índice para percorrer a string
	int	signal; // vai ser multipicar o nb no final, e vai armazenar o valor de -1 se a string começar com '-'
	long int	nb; //será o número que vamos retornar

	i = 0; // índice da string começa na posição 0, ou seja a primeira posição da string
	signal = 1; // o sinal é iniciado em 1, e se o númeri for positivo ele não será modificado
	nb = 0; // o int nb começa sem valer nada
	if (!nptr[i]) //se a string estiver vazia
		return (0); //retornamos zero
	while ((nptr[i] == '\t') || (nptr[i] == '\v') || (nptr[i] == '\f') || \
	(nptr[i] == '\n') || (nptr[i] == '\r') || (nptr[i] == ' ')) // se o início da string for espaço, ou qualquer
	//caracter de tabulação, simplesmente seguimos em frente
		i = i + 1; // vamos andando o índice de 1 em 1 enquanto for caracter de tabulação
	if (nptr[i] == '+' || nptr[i] == '-') // se for caracter de sinal, vai entrar nesse if
	{
		if (nptr[i] == '-') //caso nptr[i] seja o sinal de -
			signal *= -1; //signal passa a valer -1
		i++; //passamos para a próxima casa
	}
	while (nptr[i] >= 48 && nptr[i] <= 57) // enquanto o nptr[i] for um caracter entre 0 e 9, isto é, for numérico
	{
		// nb recebe o (nb anterior x 10) + (o número atual em valor númerico, não em valor ASCII)
		nb = (nb * 10) + (nptr[i] - 48);
		i++; // e vamos para a próxima casa
	}
	nb * signal; // multiplicamos o nb pelo sinal, para ficar negativo se a string tivesseo - no início
	if (nb > INT_MAX && nb < 0) // se for negativo ou estourar o int_max
		return (-1) // avisamos o erro
	return ((int)nb); // senão retornamos o número
}
