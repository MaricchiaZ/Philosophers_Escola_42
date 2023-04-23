/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:49 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/23 11:52:56 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void) // função pronta que pega o tempo atual,  em milissegundos desde
//(00:00:00 UTC em 1º de janeiro de 1970).
{
	struct timeval	time;

	gettimeofday(&time, NULL); // a função gettimeofday é usada para preencher essa estrutura com o tempo atual do 
	// sistema, incluindo o número de segundos desde a epoch e o número de microssegundos (1/1000000 segundos) desde o 
	// último segundo completo.
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); // depois entrega apenas os milissegundos percorridos
}

void	print_events(t_philo *philo, char *event) // função que usamos para printar as mensagens no terminal
// sinalizando cada tarefa feita pelos filósofos
{
	time_t time;
	
	pthread_mutex_lock(&philo->pdinner->msg); //travamos o uso da mensagem
	time = get_time() - philo->pdinner->init; // calculamos quanto tempo se passou do início do jantar até o momento de 
	// escrever essa mensagem
	printf("%ld %d %s\n", time, philo->id, event); // printamos a mensagem
	pthread_mutex_unlock(&philo->pdinner->msg); //destravamos o uso da mensagem
}

void	only_one( char **argv) // se apenas um filósofo for jantar, não precisamos fazer a simulação toda
// já sabemos que ele tem apenas um garfo, e como não tem um outro garfo, quando der o tempo dele morrer de inanição... ele morre.
{
	int life_time;
	
	life_time = ft_atoi(argv[2]); // salvamos o tempo que ele aguenta sem comer
	printf("0 1 %s \n", TAKEN_FORK); // ele pega o primeiro garfo (e único)
	usleep(life_time * 1000); // esperamos passar o tempo que ele aguenta sem comer
	printf("%d 1 died\n", life_time); // avisamos que ele morreu
}

int	main(int argc, char **argv) //nb_filo - t_morte - t_comer - t_dormir - qts_refei(opcional)
{
	t_pd	*pdinner;
	
	if (!check_args(argc, argv)) // conferimos se o número de args está certo e se os args esão válidos
		return (-1);
	if (ft_atoi(argv[1]) == 1) // se for apenas 1 filósofo
		return(only_one(argv), -3); // realizamos a siluação especial e retornamos -3
	pdinner = (t_pd *) ft_calloc(1, sizeof(t_pd)); // alocamos a struct e iniciamos tudo zerado
	if (!init_struct(pdinner, argv)) // inicializamos a stucts com os valores passados por argumento
		return (-1); // se a inicialização der errado retornamos -1
	if (!init_mutex(pdinner)) // inicializamos as mutex
		return (-4); // se a inicialização der errado retornamos -4
	init_philo(pdinner); // inicializamos cada filósofo
	if (!philos_threads_born(pdinner)) // inicializamos as threads de cada filósofo
	{
		free_struct(pdinner); // damos free na struct toda
		free(pdinner); // damos free no ponteiro da struct
		return (-1); // se a criação das threads der errado retornamos -1
	}
	free_struct(pdinner); // damos free na struct toda
	free(pdinner); // damos free no ponteiro da struct
	return (0); // e deu tudo certo, então retornamos 0
}
