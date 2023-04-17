/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:41 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 10:52:47 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	fork_lock(t_philo *philo)
{
	sem_wait(philo->pdinner->fork);
	sem_wait(philo->pdinner->msg);// MANDAR PRA DENTRO DO PRINT EVENT
	print_event(philo->pdinner, philo, TAKEN_FORK);
	sem_post(philo->pdinner->msg);// MANDAR PRA DENTRO DO PRINT EVENT
	if (philo->pdinner->nbr_philo == 1)  // VÊ SE PRECISA DISSO JÀ QUE TEMOS UMA FUNC PRA 1 SÒ FILO
		verify_death(philo->pdinner->time_starv + 1, philo); // VÊ SE PRECISA DISSO JÀ QUE TEMOS UMA FUNC PRA 1 SÒ FILO
	sem_wait(philo->pdinner->fork);
	sem_wait(philo->pdinner->msg);// MANDAR PRA DENTRO DO PRINT EVENT
	print_event(philo->pdinner, philo, TAKEN_FORK);
	sem_post(philo->pdinner->msg);// MANDAR PRA DENTRO DO PRINT EVENT
}

// ok
void	eat(t_philo *philo)
{
	fork_lock(philo);
	philo->last_meal = get_time();
	sem_wait(philo->pdinner->msg); // COLOCAR DENTRO DO PRINT EVENT
	print_event(philo->pdinner, philo, EATING);
	sem_post(philo->pdinner->msg); // COLOCAR DENTRO DO PRINT EVENT
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
	sem_wait(philo->pdinner->msg); // COLOCAR DENTRO DO PRINT EVENT
	print_event(philo->pdinner, philo, SLEEPING);
	sem_post(philo->pdinner->msg); // COLOCAR DENTRO DO PRINT EVENT
		verify_death(philo->pdinner->time_sleeping, philo);
}

void	think(t_philo *philo)
{
	sem_wait(philo->pdinner->msg); // COLOCAR DENTRO DO PRINT EVENT
	print_event(philo->pdinner, philo, EATING);
	sem_post(philo->pdinner->msg); // COLOCAR DENTRO DO PRINT EVENT
	usleep(500);
	while(*(int *)philo->pdinner->fork < 1)
		verify_death(1, philo);
}

void	verify_death(int time, t_philo *philo)
{
	time_t	init_time;
	
	init_time = get_time();
	while(get_time() - init_time <= time)
	{
		if (get_time() - philo->last_meal > philo->pdinner->time_starv)
		{
			sem_wait(philo->pdinner->msg); // TENTAR MANDAR PRO PRINTTTTTTTTTTT
			print_event(philo->pdinner, philo, DIED);
			sem_close(philo->pdinner->msg);
			sem_close(philo->pdinner->fork);
			free_struct(philo->pdinner);
			exit (1);
		}
		usleep(50);
	}
}
