/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:09:40 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/16 11:45:25 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*verify_death(void	*arg)
{
	t_pd	*pdinner;

	pdinner = arg;
	while (1)
	{
		sem_wait(pdinner->philo.r_fork);
		if (get_time() - pdinner->philo.last_meal > pdinner->time_starv)
		{
			sem_wait(pdinner->msg);
			print_event(pdinner, &pdinner->philo, DIED);
			sem_post(pdinner->stop);
			free_struct(pdinner);
			free(pdinner);
			exit (0);
		}
		usleep(50);
		sem_post(pdinner->philo.r_fork);
	}
	return (NULL);
}

void	create_sem_fork(t_pd *pdinner)
{
	char	*sem_name;

	sem_name = ft_strjoin("id:", ft_itoa(pdinner->philo.id));
	pdinner->philo.last_meal = pdinner->init;
	pdinner->philo.nbr_meals = 0;
	pdinner->philo.r_fork = sem_open(sem_name, O_CREAT | \
	O_EXCL, 0644, pdinner->nbr_philo);
	if (pdinner->philo.r_fork == SEM_FAILED)
		ft_putstr_fd("Sem_open error...\n", 2);
	sem_unlink(sem_name);
	free(sem_name);
	sem_unlink("fork");
	sem_unlink("msg");
	sem_unlink("stop");
	sem_unlink("nbr_meals");
	if (pthread_create(&pdinner->philo.checker, NULL, &verify_death, pdinner))
	{
		ft_putstr_fd("Pthread_create error...\n", 2);
		sem_post(pdinner->stop);
	}
	pthread_detach(pdinner->philo.checker);
}

int	init_semaphores(t_pd *pdinner)
{
	void	*fail;

	fail = SEM_FAILED;
	sem_unlink("fork");
	pdinner->fork = sem_open("fork", O_CREAT \
	| O_EXCL, 0664, pdinner->nbr_philo);
	sem_unlink("msg");
	pdinner->msg = sem_open("msg", O_CREAT | O_EXCL, 0664, 1);
	sem_unlink("stop");
	pdinner->stop = sem_open("stop", O_CREAT | O_EXCL, 0664, 0);
	sem_unlink("check_meals");
	if (pdinner->nbr_meals)
		pdinner->check_meals = sem_open("check_meals", O_CREAT \
		| O_EXCL, 0664, 0);
	if ((pdinner->nbr_meals && pdinner->check_meals == SEM_FAILED) || \
	pdinner->stop == SEM_FAILED || pdinner->fork == fail || \
	pdinner->msg == fail)
		return (ft_putstr_fd("Sem_open error...\n", 2), 0);
	return (1);
}

int	init_struct(t_pd *pdinner, char **argv)
{
	pdinner->nbr_meals = 0;
	pdinner->nbr_philo = ft_atoi(argv[1]);
	pdinner->time_starv = ft_atoi(argv[2]);
	pdinner->time_eating = ft_atoi(argv[3]);
	pdinner->time_sleeping = ft_atoi(argv[4]);
	if (argv[5])
		pdinner->nbr_meals = ft_atoi(argv[5]);
	pdinner->pid = ft_calloc(pdinner->nbr_philo, sizeof(pid_t));
	if (!pdinner->pid)
	{
		ft_putstr_fd("Malloc error...\n", 2);
		free_struct(pdinner);
		free(pdinner);
		return (0);
	}
	if (!init_thread(pdinner) || !init_semaphores(pdinner))
	{
		free(pdinner);
		return (0);
	}
	return (1);
}

void	free_struct(t_pd *pdinner)
{
	free(pdinner->pid);
	if (sem_close(pdinner->msg))
		ft_putstr_fd("sem_close() error...\n", 2);
	if (sem_close(pdinner->fork))
		ft_putstr_fd("sem_close() error...\n", 2);
	if (sem_close(pdinner->stop))
		ft_putstr_fd("sem_close() error...\n", 2);
	if (pdinner->nbr_meals && sem_close(pdinner->check_meals))
		ft_putstr_fd("sem_close() error...\n", 2);
}
