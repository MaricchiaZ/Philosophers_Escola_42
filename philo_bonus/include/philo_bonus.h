/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:00:56 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/13 11:26:22 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>

# define STOP		1
# define CONTINUE	0
# define FALSE		0
# define TRUE		1
# define EATING		11
# define THINKING	12
# define SLEEPING	13
# define TAKEN_FORK	14

typedef struct s_philo
{
	int			id;
	int			nbr_meals;
	long long	dying;
	int			need_eating;
	int			smbdy_died;
	sem_t		*dead;
	sem_t		*fork;
	sem_t		*time;
	sem_t		*eat;
	sem_t		*write;
	pthread_t	checker;
}   t_philo;

typedef struct s_philo_dinner
{
	t_philo		philo;
	int			nbr_meals;
	int			time_starv;
	int			time_eating;
	int			time_sleeping;
	int			nbr_philo;
	time_t		init;
	int			pid[200];
	t_philos	philos[200];
}   t_pdinner;

// check_args
int		check_args(int argc, char **argv);

// utils.c
void	ft_putstr_fd(char *s, int fd);
int		ft_str_isdigit(char *str);
int		chek_str_int_positive(const char *nptr);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif