/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:46:12 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 16:17:50 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life(t_philo *philo, char *event)
{
	pthread_mutex_lock(&philo->pdinner->mstop);
	if (philo->pdinner->stop)
	{
		pthread_mutex_unlock(&philo->pdinner->mstop);
		return (STOP);
	}
	pthread_mutex_unlock(&philo->pdinner->mstop);
	if (!ft_strcmp(event, EATING))
	{
		print_events(philo, EATING);
		philo->last_meal = get_time();
		philo->nbr_meals++;
		if (philo->nbr_meals == philo->pdinner->nbr_meals)
			check_limit_meals(philo->pdinner);
	}
	else
		print_events(philo, event);
	return (CONTINUE);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id % 2 == 0)
		to_sleep(philo->pdinner->time_eating / 2, philo->pdinner);
	while (philo->stop == FALSE)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->stop = life(philo, TAKEN_FORK);
		pthread_mutex_lock(philo->l_fork);
		philo->stop = life(philo, TAKEN_FORK);
		philo->stop = life(philo, EATING);
		to_sleep(philo->pdinner->time_eating, philo->pdinner);
		philo->stop = life(philo, SLEEPING);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		to_sleep(philo->pdinner->time_sleeping, philo->pdinner);
		philo->stop = life(philo, THINKING);
	}
	if (philo->r_fork == philo->l_fork)
		pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}

int	check_limit_meals(t_pd *pdinner)
{
	int	i;

	i = 0;
	while (i < pdinner->nbr_philo)
	{
		if (pdinner->philo[i].nbr_meals < pdinner->nbr_meals)
			return (FALSE);
		i++;
	}
	pdinner->stop = TRUE;
	return (TRUE);
}

void	verify_death(t_pd *pdinner)
{
	int		i;
	time_t	time;

	while (1)
	{
		i = 0;
		time = get_time();
		while (i < pdinner->nbr_philo)
		{
			if (time - pdinner->philo[i].last_meal >= pdinner->time_to_starv)
			{
				pthread_mutex_lock(&pdinner->mstop);
				print_events(&pdinner->philo[i], "died");
				pdinner->stop = TRUE;
				pthread_mutex_unlock(&pdinner->mstop);
				break ;
			}
			i++;
		}
		usleep(100);
		if (pdinner->stop == TRUE)
			return ;
	}
}

int	philos_threads_born(t_pd *pdinner)
{
	int	i;

	i = 0;
	pdinner->init = get_time();
	while (i < pdinner->nbr_philo)
	{
		pdinner->philo[i].last_meal = pdinner->init;
		if (pthread_create(&pdinner->philo[i].thread, NULL, \
		&routine, &pdinner->philo[i]))
		{
			ft_putstr_fd("Pthread_create error\n", 2);
			pthread_mutex_lock(&pdinner->mstop);
			pdinner->stop = TRUE;
			pthread_mutex_unlock(&pdinner->mstop);
			return (0);
		}
		i++;
	}
	verify_death(pdinner);
	return (1);
}
