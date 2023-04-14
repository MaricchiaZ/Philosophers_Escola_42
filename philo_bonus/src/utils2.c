/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:29:27 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 11:51:31 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *) malloc (sizeof (char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i] != '\0')
		dest[len++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		dest[len++] = s2[i++];
	dest[len] = '\0';
	return (dest);
}

static void	*str_complete(char *str, int ten, long int cpy_n, int i)
{
	while (ten >= 1)
	{
	//str[i] recebe a conversão para ASCII do número dividido pela potência de 10 (essa divisão fornece como
	// resultado apenas um dígito)
	str[i] = '0' + (cpy_n / ten); 
	//o número será agora o número sem sua casa mais alta (exemplo 1234 fica 234)
	cpy_n = cpy_n - (cpy_n / ten) * ten;
	ten = ten / 10; //potência de dez perde uma casa
	i++; //índice da string avança uma casa
	}
	str[i] = '\0'; // a última posição da string recebe o byte nulo
	return (str); //retornamos a strig str já preenchida
}

//função principal - COMEÇE LENDO POR AQUI
char	*ft_itoa(int n) //recebe um int a partir do qual fará a string
{
	int			signal_loc; //vai reservar o início da string para o sinal
	int			ten; //receberá a potência de 10 referente ao número
	char		*str; //ponteiro que receberá a string
	int			i; //índice de casas que o número ocupará, será usado para alocar
	long int	cpy_n; //receberá a cópia do número passado, é em long int
	//para não estourar o int max, caso seja passado o int min;

	signal_loc = 0; //inicia em zero, pois não sabemos se a string terá sinal
	ten = 1; // a pontência de dez inicia-se em 1
	i = 1; // se o número existe, pelo menos uma unidade ele tem
	cpy_n = n; //recebe a cópia do número passado
	if (cpy_n < 0) // se o número for negativo
	{
		signal_loc = 1; //reservarvamos o início da string para o sinal
		cpy_n = cpy_n * -1; //passamos o número para positivo, para podemos trabalhar
	}
	while (ten <= cpy_n / 10) //enquanto a potência de dez não alcançar o mesmo número de casas do número
	{
		ten = ten * 10; //multiplicamos por dez
		i++; // e o número de casas aumenta conforme o tam do número
	}
	// o ponteiro que criamos recebe a malocagem do número de casas do número + sinal se tiver + 1 para o byte nulo
	// o byte nulo serve para finalizar a string
	str = (char *) malloc(sizeof(char) * (i + signal_loc + 1)); 
	if (signal_loc == 1) // se o número tiver sinal, ito é signal_loc foi 1
		str[0] = '-'; //str na posição 0 recebe o sinal de -
	str_complete(str, ten, cpy_n, signal_loc); //chamamos a função de cima que vai preencher a string e
	// essa função retorna a string já preenchida
	return (str); // retormanos a string
}

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
