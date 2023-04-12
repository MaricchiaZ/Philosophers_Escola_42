/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:46:12 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/11 20:55:19 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life(t_philo *philo, int event)
{
	pthread_mutex_lock(&philo->pdinner->msg);
	if (philo->pdinner->stop)
	{
		pthread_mutex_unlock(&philo->pdinner->msg);
		return (STOP);
	}
	if (event == EATING)
	{
		print_events(philo, "is eating");
		philo->last_meal = get_time();
	}
	else if (event == THINKING)
		print_events(philo, "is thinking");
	else if (event == SLEEPING)
	{
		print_events(philo, "is sleeping");
		philo->nbr_meals++; // nao deveria estar em pensando???????????????????????????????
		if (philo->nbr_meals == philo->pdinner->nbr_meals)
			check_limit_meals(philo->pdinner);
	}
	else if (event == TAKEN_FORK)
		print_events(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->pdinner->msg);
	return (CONTINUE);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->id %2L == 0)
		to_sleep(philo->pdinner->time_eating / 2L, philo->pdinner);
	while (philo->stop == false)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->stop = life(philo, TAKEN_FORK);
		if (philo->r_fork == philo->l_fork)
			break;
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

int check_limit_meals(t_pd *pdinner)
{
	size_t	i;

	i = 0;
	while (i < pdinner->nbr_philo)
	{
		if (pdinner->philo[i].nbr_meals < pdinner->nbr_meals)
			return (false);
		i++;
	}
	pdinner->stop = true;
	return (true);
}

void	verify_death(t_pd *pdinner) // verifica se tds os filósofos estão vindo
{
	size_t	i; // contador pra percorrer os filos
	time_t	time; // tempo atual

	while (1) // ciclo eterno
	{
		i = 0; //
		pthread_mutex_lock(&pdinner->msg); // travamos o uso das mensagens
		time = get_time(); // conferimos o tempo de agora
		while (i < pdinner->nbr_philo) // enquanto nao passarmos por todos os filos
		{
			if (time - pdinner->philo[i].last_meal >= pdinner->time_to_starv) // vemos se o tempo transcorrido desde a última refeição é maior ou igual ao tempo pro filo morrer de inanição
			{
				print_events(&pdinner->philo[i], "died"); //printamos a morte do filo
				pdinner->stop = true; // vamos parar o programa
				break; // saímos do while
			}
			i++; // vamos pro próximo filósofo
		}
		pthread_mutex_unlock(&pdinner->msg); // destravamos o uso das mensagens
		if (pdinner->stop == true) // se temos o aviso pra parar...
			return ; // retornamos
	}
}

int	philos_threads_born(t_pd *pdinner)
{
	size_t	i;

	i = 0;
	pdinner->init = get_time(); // anotamos o horário que inciamos o programa
	while (i < pdinner->nbr_philo) // enquanto n passarmos por todos os filósofos
	{
		pdinner->philo[i].last_meal = pdinner->init;
		if (pthread_create(&pdinner->philo[i].thread, NULL, &routine, &pdinner->philo[i]))
		{
			ft_putstr_fd("Pthread_create error\n", 2);
			pthread_mutex_lock(&pdinner->msg);
			pdinner->stop = true;
			pthread_mutex_unlock(&pdinner->msg);
			return (0);
		}
		i++;
	}
	verify_death(pdinner);
	return (1);
}