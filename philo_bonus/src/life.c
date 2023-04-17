/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:41 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 11:37:55 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*life(t_philo *aux)
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

void	eat(t_philo *philo)
{
	sem_wait(philo->pdinner->fork);
	print_event(philo->pdinner, philo, TAKEN_FORK);
	sem_wait(philo->pdinner->fork);
	print_event(philo->pdinner, philo, TAKEN_FORK);
	philo->last_meal = get_time();
	print_event(philo->pdinner, philo, EATING);
	philo->nbr_meals++;
	if (philo->nbr_meals == philo->pdinner->nbr_meals)
	{
		sem_post(philo->pdinner->fork);
		sem_post(philo->pdinner->fork);
		sem_close(philo->pdinner->fork);
		sem_close(philo->pdinner->msg);
		free_struct(philo->pdinner);
		free(philo->pdinner);
		exit(0);
	}
	verify_death(philo->pdinner->time_eating, philo);
	sem_post(philo->pdinner->fork);
	sem_post(philo->pdinner->fork);
}

void	to_sleep(t_philo *philo)
{
	print_event(philo->pdinner, philo, SLEEPING);
	verify_death(philo->pdinner->time_sleeping, philo);
}

void	think(t_philo *philo)
{
	print_event(philo->pdinner, philo, EATING);
	usleep(500);
	while(*(int *)philo->pdinner->fork < 1)
		verify_death(1, philo);
}

void	verify_death(int time, t_philo *philo)
{
	time_t	init_time;
	time_t	time_death;
	
	init_time = get_time();
	while(get_time() - init_time <= time)
	{
		if (get_time() - philo->last_meal > philo->pdinner->time_starv)
		{
			sem_wait(philo->pdinner->msg);
			time_death = get_time() - philo->pdinner->init;
			printf("%ld %d %s\n", time_death, philo->id, "die");
			sem_close(philo->pdinner->msg);
			sem_close(philo->pdinner->fork);
			free_struct(philo->pdinner);
			exit (1);
		}
		usleep(100);
	}
}
