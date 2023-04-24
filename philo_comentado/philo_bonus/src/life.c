/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:41 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/24 07:50:08 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*life(t_philo *aux) // função que representa as atividades que o filósofo faz
{
	aux->last_meal = get_time(); // salvamos o tempo atual como a última refeição que ele fez
	if (!(aux->id % 2)) // os filósofos de número par ficarão uns instantes em espera
	// para evitar que todos iniciem ao mesmo tempo, e que cada um pegue um garfo... isso
	// faria com que cada um tivesse um garfo e ninguém pudesse comer ... todos morreriam de fome
		verify_death(aux->pdinner->time_eating, aux); // verificamos se alguém morreu
	while (1) // while infinito de comer, dormir e pensar (oooowww vida boa!!!)
	{
		eat(aux); // coloca o filósofo para comer pelo tempo determinado
		to_sleep(aux); // coloca o filósofo para dormir pelo tempo determinado
		think(aux);// o filósofo pensa no tempo que sobrar até comer de novo
	}
	exit(0); // finalizamos a simulação
}

void	eat(t_philo *philo) // função responsável pela refeição do filósofo
{
	sem_wait(philo->pdinner->fork); // travamos o primeiro garfo
	print_event(philo->pdinner, philo, TAKEN_FORK); // avisamos que o filósofo pegou o garfo
	sem_wait(philo->pdinner->fork); // travamos o segundo garfo
	print_event(philo->pdinner, philo, TAKEN_FORK); // avisamos que o filósofo pegou o garfo
	philo->last_meal = get_time(); // atualizamos o horário da última refeição
	print_event(philo->pdinner, philo, EATING); // avisamos que o filósofo está comendo
	philo->nbr_meals++; // atualizamos o número de refeições feitas
	if (philo->nbr_meals == philo->pdinner->nbr_meals) // se o número máximo de refeições for atingido
	{
		sem_post(philo->pdinner->fork); // soltamos o primeiro garfo
		sem_post(philo->pdinner->fork); // soltamos o segundo garfo
		sem_close(philo->pdinner->fork); // "liberamos" o semáforo dos garfos
		sem_close(philo->pdinner->msg); // "liberamos" o semáforo das mensagens
		free_struct(philo->pdinner); // liberamos a struct principal
		free(philo->pdinner); // liberamos o ponteiro da struct
		exit(0); // finalizamos o programa filho (responsável pelo filósofo)
	}
	verify_death(philo->pdinner->time_eating, philo); // colocamos o filósofo em espera
	// pelo tempo determinado que ele deve comer E conferimos se alguém morreu
	sem_post(philo->pdinner->fork);  // soltamos o primeiro garfo
	sem_post(philo->pdinner->fork); // soltamos o segundo garfo
}

void	to_sleep(t_philo *philo) // função que coloca o filósofo pra dormir
{
	print_event(philo->pdinner, philo, SLEEPING); // avisa que ele está dormindo
	verify_death(philo->pdinner->time_sleeping, philo); //coloca ele em espera pelo tempo que o filósofo
	// deve dormir E veficamos se alguém morreu nesse tempo
}

void	think(t_philo *philo)  // função que coloca o filósofo pra pensar
{
	print_event(philo->pdinner, philo, THINKING); // avisa que ele está pensando
	usleep(500); // atrasamos 1/2 segundo para evitar data racing
	while(*(int *)philo->pdinner->fork < 1)// vai pensar em quanto não tiver nenhum garfo livre
		verify_death(1, philo); //coloca ele em espera enquanto o número de garfos livres for zero
	// E veficamos se alguém morreu nesse tempo
}

void	verify_death(int time, t_philo *philo) // põe o filósofo em espera e verifica as mortes
{
	time_t	init_time; // vai receber o tempo atual
	time_t	time_death; // pra salvar o momento que o filósofo morreu
	t_pd	*aux; // pra receber o ponteiro da struct principal que devemos liberar
	
	init_time = get_time(); // salva o tempo atual
	while(get_time() - init_time <= time) //vê se o tempo de espera é menor do que o tempo dele morrer 
	// de inanição
	{
		if (get_time() - philo->last_meal > philo->pdinner->time_starv) // se ultrapassou o tempo até morrer de fome
		{ // o filósofo morre
			sem_wait(philo->pdinner->msg); // travamos o uso das mensagens
			time_death = get_time() - philo->pdinner->init; // salvamos o horário da morte
			printf("%ld %d %s\n", time_death, philo->id, "die"); // avisamos que ele morreu
			sem_close(philo->pdinner->msg); // liberamos o semáforo das mensagens
			sem_close(philo->pdinner->fork); // liberamos o semáforo dos garfos
			aux = philo->pdinner; // salvamos o ponteiro da struct principal
			free_struct(philo->pdinner); // liberamos a struct
			free(aux);// liberamos o ponteiro da struct principal
			exit (1); // finalizamos o processo filho (que representa o filósofo)
		}
		usleep(100); //o filósofo fica em espera 1/10 de segundo (isso se repete até se completar o 
		// tempo que o filósofo deve ficar em espera (pq ele está em uma ação))
	}
}
