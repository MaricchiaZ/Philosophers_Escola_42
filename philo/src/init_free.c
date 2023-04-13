/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:36:05 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/13 15:00:10 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_pd	*pdinner) // inicializaremos os valores de cada filósofo
{
	size_t	i;
	
	i = 0;
	while (i < pdinner->nbr_philo) // enquanto não inicializar todos os filósofos
	{
		pdinner->philo[i].stop = FALSE;
		pdinner->philo[i].nbr_meals = 0;
		pdinner->philo[i].id = i + 1; // o id do filo é por ordem de chegada "de criação"
		pdinner->philo[i].pdinner = pdinner; // todos apontam pra mesa de jantar
		pdinner->philo[i].r_fork = &pdinner->fork[i]; // o garfo da mão direita eles trouxeram de casa
		if (i == pdinner->nbr_philo - 1) // se chegamos no último philo
			pdinner->philo[i].l_fork = &pdinner->fork[0]; // o garfo da esquerda é emprestado filo 1
		else // senão
			pdinner->philo[i].l_fork = &pdinner->fork[i + 1]; // o garfo da esquerda é emprestado do próximo filo (é o garfo direito q o próximo filo trouxe de casa)
		i++;
	}
}

int	init_struct(t_pd *pdinner, char **argv) // vamos iniciar a struct e salvar os args nas variáveis
{
	pdinner->stop = 0;
	pdinner->nbr_meals = 0;
	pdinner->nbr_philo = ft_atoi(argv[1]); // convertemos o argv em número e salvamos na variável correspondente
	pdinner->time_to_starv = ft_atoi(argv[2]); // salvamos o argv virado int na variável correspondente
	pdinner->time_eating = ft_atoi(argv[3]); // salvamos o argv virado int na variável correspondente
	pdinner->time_sleeping = ft_atoi(argv[4]); // salvamos o argv virado int na variável correspondente
	if (argv[5]) // se tievr o último arg, (número de refeições q cada um deve fazer...)
		pdinner->nbr_meals = ft_atoi(argv[5]); // salvamos o argv virado int na variável correspondente
	pdinner->philo = ft_calloc(pdinner->nbr_philo, sizeof(t_philo)); // allocamos e iniciamos zerado o array de filósofos
	pdinner->fork = ft_calloc(pdinner->nbr_philo, sizeof(pthread_mutex_t)); // allocamos e iniciamos zerado o array de garfos
	if (!pdinner->philo || !pdinner->fork) // se a alocação der errado
	{
		free(pdinner->philo);
		free(pdinner->fork); // limpamos a allocação 
		ft_putstr_fd("Malloc error...\n", 2); // avisamos o erro de malloc
		return (0); // retornamos erro (0 = false)
	}
	return (1); // se der td certo, retornamos 1
}

int	init_mutex(t_pd *pdinner) // vamos iniciar as mutex
{
	int i;

	i = 0;
	while (i < (int)pdinner->nbr_philo) //vamos iniciar uma mutex para cada garfo
	{
		if (pthread_mutex_init(&pdinner->fork[i], NULL)) // iniciamos a mutex dos garfos
			break; // se a func pthread_mutex_init() voltar 1 é pq temos um erro// aí paramos esse while
		i++;
	}
	if (i-- != (int)pdinner->nbr_philo || pthread_mutex_init(&pdinner->msg, NULL) || pthread_mutex_init(&pdinner->mstop, NULL)) 
	{
		while (i >= 0)
			pthread_mutex_destroy(&pdinner->fork[i--]);
		ft_putstr_fd("Pthread error...\n", 2);
		free(pdinner->philo);
		free(pdinner->fork);
		return (0); // retornamos avisando o erro
	}
	return (1); // retornamos avisando que está tudo ok
}

void	free_struct(t_pd *pdinner)
{
	size_t	i;

	i = 0;
	while (i < pdinner->nbr_philo) // enquanto i < número de filos
	{
		if (pthread_join(pdinner->philo[i].thread, NULL)) //se tiver erro de join
			ft_putstr_fd("Pthread_join error...\n", 2); // avisamos o erro
		i++;
	}
	free(pdinner->philo); // damos free no philo
	i = 0;
	while (i < pdinner->nbr_philo)
	{
		if (pthread_mutex_destroy(&pdinner->fork[i])) //se tiver erro na função de destroi e desaloca os mutex dos garfos
			ft_putstr_fd("Pthread_mutex_destroy error...\n", 2); // avisamos o erro
		i++;
	}
	free(pdinner->fork);
	if (pthread_mutex_destroy(&pdinner->msg)) //se tiver erro na função de destroi e desaloca o mutex da func de notificar as ações dos filósofos
		ft_putstr_fd("Pthread_join error...\n", 2); // avisamos o erro
	if (pthread_mutex_destroy(&pdinner->mstop)) //se tiver erro na função de destroi e desaloca o mutex da func de notificar as ações dos filósofos
		ft_putstr_fd("Pthread_join error...\n", 2); // avisamos o erro
	free(pdinner);
}
