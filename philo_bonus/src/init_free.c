/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:09:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/16 13:59:33 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_thread(t_pd *pdinner)
{
	t_philo	*aux; // ponteiro auxuliar para percorrer os philos
	int		i;

	aux = pdinner->philo;
	i = pdinner->nbr_philo;
	pthread_mutex_init(&pdinner->fork, NULL);
	pthread_mutex_init(&pdinner->msg, NULL);
	pthread_mutex_init(&pdinner->stop_mutex, NULL);
	pthread_mutex_init(&pdinner->time_meal, NULL);
	pdinner->init = get_time;
	while (i)
	{
		pthread_create(&aux->thread, NULL, &life, aux);
		aux = aux->next;
		i--;
	}
	verify_death(pdinner);
	i = pdinner->nbr_philo;
	while (i)
	{
		pthread_join(aux->thread, NULL);
		aux = aux->next;
		i--;
	}
}

static void	add_list(t_philo *philo, t_pd *pdinner, int i)
{
	t_philo	*next_philo; // ponteiro pro novo filo q vamos por na lista
	t_philo	*prev_philo; // ponteiro pro novo anterior do que estamos pondo na lista

	prev_philo = philo;
	next_philo = (t_philo *) calloc (1, sizeof(t_philo));
	pthread_mutex_init(&next_philo->fork, NULL);
	next_philo->id = i + 1;
	next_philo->nbr_meals = 0;
	next_philo->pdinner = pdinner;
	while (philo->next != philo->prev) // vamos avançar até o último philo da lista (ou já sentado na mesa)
		philo = philo->next; //avançando
	next_philo->next = next_philo;
	next_philo->prev = prev_philo;
	prev_filo->prev = next_philo;
}

void	init_philo(t_pd *pdinner)
{
	int i;

	i = 0;
	pdinner->philo = (t_philo* ) ft_calloc(1, sizeof(t_philo)); // alocamos a struct do philo
	pthread_mutex_init(&pdinner->philo->fork, NULL); // e iniciamos ÚNICO garfo que ele tem como um mutex
	pdinner->philo.id = 1;
	pdinner->philo.nbr_meals = 0;
	pdinner->philo.next = NULL;
	pdinner->philo.prev = NULL;
	pdinner->philo.pdinner = pdinner;
	while(i < pdinner->nbr_philo - 1)
		add_list(pdinner->philo, pdinner, i + 1);
}

void	init_struct(t_pd *pdinner, char **argv)
{
	pdinner->nbr_meals = 0;
	pdinner->nbr_philo = ft_atoi(argv[1]);
	pdinner->time_starv = ft_atoi(argv[2]);
	pdinner->time_eating = ft_atoi(argv[3]);
	pdinner->time_sleeping = ft_atoi(argv[4]);
	if (argv[5])
		pdinner->nbr_meals = ft_atoi(argv[5]);
	pdinner->pid = ft_calloc(pdinner->nbr_philo, sizeof(pid_t));
}

void	free_struct(t_pd *pdinner)
{
	while (pdinner->nbr_philo > 1)
	{
		pdinner->philo = pdinner->philo->next;
		free (pdinner->philo->prev);
		pdinner->nbr_philo--;
	}
	free (pdinner->philo);
}
