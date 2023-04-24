/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:51 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/24 07:43:27 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void) // função pronta que pega o tempo atual,  em milissegundos desde
//(00:00:00 UTC em 1º de janeiro de 1970).
{
	struct timeval	time;

	gettimeofday(&time, NULL); // a função gettimeofday é usada para preencher essa estrutura com o tempo atual do 
	// sistema, incluindo o número de segundos desde a epoch e o número de microssegundos (1/1000000 segundos) desde o 
	// último segundo completo.
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000)); // depois entrega apenas os milissegundos percorridos
}

void	print_event(t_pd *pdinner, t_philo *philo, char *event) // imprime no terminal as mensagens 
// das ações feitas pelos filósofos
{
	time_t	time; // reseberá o tempo transcorrido do início da simulação até a hora de imprimir a mensagem

	sem_wait(pdinner->msg); // travamos o uso da mensagem
	time = get_time() - pdinner->init; // descobrimos o tempo transcorrido do início da simulação até a hora de imprimir
	printf("%ld	%d %s\n", time, philo->id, event); // imprimimos a mensagem
	sem_post(pdinner->msg); // destravamos o uso da mensagem
	
}

void	only_one(char **argv) // se tiver um só filósofo, não precisamos iniciar os semáforos nem criar
// vários processos, então podemos fazer uma simulação simplificada
{
	pid_t	pid; // recebe o fork que representará esse único filósofo

	pid = fork(); // criamos um processo pra esse filósofo
	if (pid == 0) // se for o processo filho
	{
		printf("0 1 taken a fork\n"); // avisamos que ele pegou um garfo (o único que tem)
		usleep(1000 * ft_atoi(argv[2])); // esperamos pelo tempo determinado até ele morrer de fome
		printf("%s 1 died\n", argv[2]); // avisamos que ele morreu
	}
	waitpid(pid, NULL, 0); // processo pai espera o processo filho finalizar
}

int	main(int argc, char **argv)
{
	t_pd	*pdinner; // a struct principal

	if (!check_args(argc, argv)) // se a checagem dos argumentos encontrar um erro
		return (-1); // finalizamos a simulação
	if (ft_atoi(argv[1]) == 1) // se for apenas 1 filósofo
		return (only_one(argv), 0); // rodamos a função de um só filósofo e finalizamos a simulação
	pdinner = (t_pd *) ft_calloc(1, sizeof(t_pd)); // alocamos a struct principal e zeramos seu conteúdo
	init_struct(pdinner, argv); // iniciamos a struct com os valores presentes nos argvs
	init_philo_and_sem(pdinner); // iniciamos os filósofos e colocamos na lista ligada e iniciamos os semáforos
	create_philo_process(pdinner); // criamos os processos filhos que representarão os filósofos
	sem_close(pdinner->msg); // fechamos o semáforo das mensagens
	sem_close(pdinner->fork); // fechamos o semáforo dos garfos
	free_struct(pdinner); // liberamos a struct principal
	free(pdinner); // liberamos o ponteiro da struct principal
	return (0); // finalizamos a simulação
}
