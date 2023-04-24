/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:09:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/23 13:54:48 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philo_process(t_pd *pdinner) // vamos criar um processo para cada filósofo
{
	int		nbr_philo; // inteiro que vai receber o número de filósofos
	t_philo	*aux; // ponteiro auxiliar para percorrer os nós da lista ligada

	nbr_philo = pdinner->nbr_philo; // recebe o número de filósofos que estarão no jantar
	aux = pdinner->philo; // recebe o ponteiro para o primeiro filósofo
	pdinner->init = get_time(); // salvamos o tempo em que a simulação vai se iniciar
	while(nbr_philo > 0) // enquanto não criarmos todos os filósofos
	{
		aux->pid = fork(); // fazemos um fork - ISTO É duplicamos o processo principal, e esse novo processo criado
		// é um filósofo (repetiremos isso até criar todos os filósofos)
		if (aux->pid == 0) // se estivermos no processo filho (isto é no filósofo criado)
			life(aux); // rodamos as funções pertinentes a vida do filósofo
		aux = aux->next; // vamos para o próximo filósofo
		nbr_philo--; // decrementamos 1 no número de filósofos que ainda precisamos criar
	}
	wait_process(pdinner); // o processo pao espera os processos (filhos ou filósofos) que estão rodando ainda
}

static void	add_list(t_philo *philo, t_pd *pdinner, int i)
{
	t_philo	*next_philo; // ponteiro pro novo filósofo que vamos por na lista
	t_philo	*prev_philo; // ponteiro pro novo anterior do que estamos pondo na lista

	prev_philo = philo; // filósofo anterior recebe o filo que já tinhamos
	next_philo = (t_philo *) calloc (1, sizeof(t_philo)); // alocamos o novo filo
	next_philo->id = i + 1; // ele recebe o id dele
	next_philo->nbr_meals = 0; // número de refeições já feitas é zero
	next_philo->pdinner = pdinner; // ele recebe o ponteiro pra struct "mesa de jantar"
	while (philo->next != prev_philo) // vamos avançar até o último philo da lista (ou já sentado na mesa)
		philo = philo->next; //avançando
	philo->next = next_philo; // o novo filósofo é o próximo do ultimo que já estava sentado
	next_philo->next = prev_philo; // se não sentar mais nenhum o próximo dele é o anterior
	next_philo->prev = philo; // o anterior do novo filósofo é ultimo que já estava sentado
	prev_philo->prev = next_philo; // o anterior do que já estava sentado é o último que sentou
}

void	init_philo_and_sem(t_pd *pdinner) // iniciando os filósofos e os semáforos
{
	int i;

	i = 0;
	pdinner->msg = sem_open("msg", O_CREAT, 0664, 1); // iniciamos o semáforo para uso das mensagems com o valor de 1
	pdinner->fork = sem_open("fork", O_CREAT, 0664, pdinner->nbr_philo); // iniciamos o semáforo dos garfos com o valor 
	// do número de filósofos sentados à mesa
	sem_unlink("msg"); // limpamos os semáforos para eles iniciarem limpos
	sem_unlink("fork");  // limpamos os semáforos para eles iniciarem limpos
	pdinner->philo = (t_philo* ) ft_calloc(1, sizeof(t_philo)); // alocamos um filósofo
	pdinner->philo->id = 1; // inicialmente o id dele é 1
	pdinner->philo->nbr_meals = 0; // o número de refeições é zero
	pdinner->philo->next = pdinner->philo; //o próximo filósofo da mesa é ele mesmo
	pdinner->philo->prev = pdinner->philo;  //o próximo filósofo anterior da mesa é ele mesmo
	pdinner->philo->pdinner = pdinner; // ele recebe o ponteiro pra struct "mesa de jantar"
	while(++i < pdinner->nbr_philo) // enquanto não passarmos por todos os filósofos
		add_list(pdinner->philo, pdinner, i); // vamos adicionando eles na lista ligada
}

void	init_struct(t_pd *pdinner, char **argv) // vamos iniciar a struct e salvar os args nas variáveis
{
	pdinner->nbr_meals = -1;  // não sabemos se o número de refeições dos filósofos vai existir, então iniciamos com -1
	pdinner->nbr_philo = ft_atoi(argv[1]);  // convertemos o argv em número e salvamos na variável correspondente
	pdinner->time_starv = ft_atoi(argv[2]);  // salvamos o argv virado int na variável correspondente
	pdinner->time_eating = ft_atoi(argv[3]);  // salvamos o argv virado int na variável correspondente
	pdinner->time_sleeping = ft_atoi(argv[4]);  // salvamos o argv virado int na variável correspondente
	if (argv[5]) // se tievr o último arg, (número de refeições q cada um deve fazer...)
		pdinner->nbr_meals = ft_atoi(argv[5]); // salvamos o argv virado int na variável correspondente
}

void	free_struct(t_pd *pdinner) // função para dar free em toda struct
{
	if (pdinner->nbr_philo == 1) // se só sobrou um filósofo
		free (pdinner->philo); // damos free no ponteiro para os filos (que acomoda esse último filósofo)
	else // se tiver mais de um filósofo
	{
		while (pdinner->nbr_philo > 1) // enquanto tem mais de um filósofo
		{
			pdinner->philo = pdinner->philo->next; // apontamos para o próximo
			free (pdinner->philo->prev); // damos free no anterior do próximo
			pdinner->nbr_philo--; // diminuímos o número de filos existentes
		}
		free (pdinner->philo); // damos free no filo
	}
}
