/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:29:41 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 17:33:49 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	life(t_pd *pdinner, char *event)
{
	sem_wait(pdinner->msg);
	sem_wait(pdinner->philo.r_fork);
	if (!ft_strcmp(event, EATING))
	{
		print_event(pdinner, &pdinner->philo, EATING);
		pdinner->philo.last_meal = get_time();
		pdinner->philo.nbr_meals++;
		if (pdinner->philo.nbr_meals == pdinner->nbr_meals)
			sem_post(pdinner->check_meals);
	}
	else
		print_event(pdinner, &pdinner->philo, event);
	sem_post(pdinner->philo.r_fork);
	sem_post(pdinner->msg);
}

void	to_sleep(time_t microsec, t_pd *pdinner)
{
	time_t	init;

	init = get_time();
	while (get_time() - init < microsec)
	{
		if (pdinner->nbr_philo < 100)
			usleep(100);
		else
			usleep(1000);
	}
}

void	*routine(t_pd *pdinner)
{
	if (pdinner->philo.id > pdinner->nbr_philo / 2)
		to_sleep(pdinner->time_eating / 2, pdinner);
	while (1)
	{
		sem_wait(pdinner->fork);
		life(pdinner, TAKEN_FORK);
		sem_wait(pdinner->fork);
		life(pdinner, TAKEN_FORK);
		life(pdinner, EATING);
		to_sleep(pdinner->time_eating, pdinner);
		life(pdinner, SLEEPING);
		sem_post(pdinner->fork);
		sem_post(pdinner->fork);
		to_sleep(pdinner->time_sleeping, pdinner);
		life(pdinner, THINKING);
	}
	return (NULL);
}

int	create_philo(t_pd *pdinner)
{
	int	i;

	i = 0;
	pdinner->init = get_time();
	while (i < pdinner->nbr_philo)
	{
		pdinner->philo.id = i + 1;
		pdinner->pid[i] = fork();
		if (pdinner->pid[i] == -1)
		{
			ft_putstr_fd("fork fail...\n", 2);
			i--;
			while (--i >= 0)
				kill(pdinner->pid[i], SIGKILL);
			return (free_struct(pdinner), free(pdinner), 0);
		}
		else if (pdinner->pid[i] == 0)
		{
			create_sem_fork(pdinner);
			routine(pdinner);
		}
		i++;
	}
	sem_wait(pdinner->stop);
	return (1);
}

void	kill_philo(t_pd *pdinner)
{
	int	i;

	i = 0;
	while (i < pdinner->nbr_philo)
	{
		kill(pdinner->pid[i], SIGKILL);
		i++;
	}
}
