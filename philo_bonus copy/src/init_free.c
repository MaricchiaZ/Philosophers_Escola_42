/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:09:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 10:51:56 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *teste(t_philo	*aux)
{
	aux->last_meal = get_time();
	if (!(aux->id % 2))
		verify_death(aux->pdinner->time_eating, aux);
	while (1)
	{
		eat(aux);
		to_sleep(aux);
		think(aux);
	}
	exit(0);
}

void	create_philo_process(t_pd *pdinner)
{
	int		nbr_philo;
	t_philo	*aux;

	nbr_philo = pdinner->nbr_philo;
	aux = pdinner->philo;
	pdinner->init = get_time();
	while(nbr_philo > 0)
	{
		aux->pid = fork();
		if (aux->pid == 0)
		{
			teste(aux);
		}
		aux = aux->next;
		nbr_philo--;
	}
	wait_process(pdinner);
}

static void	add_list(t_philo *philo, t_pd *pdinner, int i)
{
	t_philo	*next_philo; // ponteiro pro novo filo q vamos por na lista
	t_philo	*prev_philo; // ponteiro pro novo anterior do que estamos pondo na lista

	prev_philo = philo;
	next_philo = (t_philo *) calloc (1, sizeof(t_philo));
	next_philo->id = i + 1;
	next_philo->nbr_meals = 0;
	next_philo->pdinner = pdinner;
	while (philo->next != prev_philo) // vamos avançar até o último philo da lista (ou já sentado na mesa)
		philo = philo->next; //avançando
	philo->next = next_philo;
	next_philo->next = prev_philo;
	next_philo->prev = philo;
	prev_philo->prev = next_philo;
}

void	init_philo_and_sem(t_pd *pdinner)
{
	int i;

	i = 0;
	pdinner->msg = sem_open("msg", O_CREAT, 0664, 1);
	pdinner->fork = sem_open("fork", O_CREAT, 0664, pdinner->nbr_philo);
	sem_unlink("msg");
	sem_unlink("fork");
	pdinner->philo = (t_philo* ) ft_calloc(1, sizeof(t_philo));
	pdinner->philo->id = 1;
	pdinner->philo->nbr_meals = 0;
	pdinner->philo->next = pdinner->philo;
	pdinner->philo->prev = pdinner->philo;
	pdinner->philo->pdinner = pdinner;
	while(++i < pdinner->nbr_philo)
		add_list(pdinner->philo, pdinner, i);
}

void	init_struct(t_pd *pdinner, char **argv)
{
	pdinner->nbr_meals = -1;
	pdinner->nbr_philo = ft_atoi(argv[1]);
	pdinner->time_starv = ft_atoi(argv[2]);
	pdinner->time_eating = ft_atoi(argv[3]);
	pdinner->time_sleeping = ft_atoi(argv[4]);
	if (argv[5])
		pdinner->nbr_meals = ft_atoi(argv[5]);
}

void	free_struct(t_pd *pdinner)
{
	if (pdinner->nbr_philo == 1)
		free (pdinner->philo);
	else
	{
		while (pdinner->nbr_philo > 1)
		{
			pdinner->philo = pdinner->philo->next;
			free (pdinner->philo->prev);
			pdinner->nbr_philo--;
		}
		free (pdinner->philo);
	}
}
