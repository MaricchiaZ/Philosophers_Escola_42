/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 07:16:17 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/11 20:55:37 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
int	chek_str_int_positive(const char *nptr)
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
	nb = nb * signal; // multiplicamos o nb pelo sinal, para ficar negativo se a string tivesseo - no início
	if (nb > INT_MAX && nb < 0) // se for negativo ou estourar o int_max
		return (0); // avisamos o erro
	return (1); // senão retornamos ok
}

//esta função tranforma uma string de char numérico em um inteiro
int	ft_atoi(const char *nptr)
{
	int	i; // índice para percorrer a string
	int	signal; // vai ser multipicar o nb no final, e vai armazenar o valor de -1 se a string começar com '-'
	int	nb; //será o número que vamos retornar

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
	return (nb * signal); // multiplicamos o nb pelo sinal, para ficar negativo se a string tivesseo - no início
}

void	*ft_calloc(size_t nmemb, size_t size) //recebe o número de membros e o tam de cada um
{
	size_t	aux; //variável aux
	void	*tab; //ponteiro para a memória que alocaremos
	int		i; //índice auxiliar para percorrer a memória

	if (nmemb == 0) // se número de membros for 0, retornamos NULL
		return (NULL);
		// se número de membros ou o size, ou a multiplicação dos dois for maior que o size_t max, retornamos NULL
	if (nmemb > 2147483647 || size > 2147483647 || size * nmemb > 2147483647)
		return (NULL);
	aux = (size) * (nmemb); //aux armazena a quantidade de bytes referente a n membros de tamanho size
	tab = malloc(aux); //nosso ponteiro recebe a malocação da quantidade de bytes
	if (tab == NULL) // se o malloc der errado, tab será igual a NULL
		return (NULL); // então retornamos NULL
	//ft_bzero(tab, aux); // caso a malocação tenha dado certo "zeramos" a memória dos i bytes
	i = 0; //índice começa no 0
	while (nmemb && tab) //enquanto a string s e o n forem verdadeiros, existirem, ou seja, não forem nulos
	{
		*(unsigned char *)(tab + i) = '\0'; //fazemos um cast do ponteiro void de s para um ponteiro unsigned char
		// e somamos o s ao índice, fazendo uma aritmérica de ponteiro, 
		i++;//e  cada byte que passamos recebe o byte nulo '\0' 
		nmemb--; //decrementamos o n para agir apenas nos n bytes pedidos
	}
	return (tab); //retornamos nosso ponteiro para os bytes alocados e "limpos"
}
