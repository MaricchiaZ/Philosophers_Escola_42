/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:16:46 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/12 16:33:40 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
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

typedef struct s_philo_dinner   t_pd;

typedef struct  s_philo
{
	size_t			id;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	time_t			last_meal;
	size_t			nbr_meals;
	int				stop;
	t_pd			*pdinner;
}   t_philo;

typedef struct s_philo_dinner
{
	t_philo			*philo;
	size_t			nbr_philo;
	time_t			time_to_starv;
	time_t			time_eating;
	time_t			time_sleeping;
	size_t			nbr_meals;
	pthread_mutex_t	*fork;
	pthread_mutex_t	msg;
	time_t			init;
	int				stop;
}   s_pd;

// check_args.c
int		check_args(int argc, char **argv);

// init_free.c
void	init_philo(t_pd	*pdinner);
int		init_struct(t_pd *pdinner, char **argv);
int		init_mutex(t_pd *pdinner);
void	free_struct(t_pd *pdinner);

// life_philos.c
int		life(t_philo *philo, int event);
void	*routine(void *arg);
int 	check_limit_meals(t_pd *pdinner);
void	verify_death(t_pd *pdinner);
int		philos_threads_born(t_pd *pdinner);

// main.c
time_t	get_time(void);
void	print_events(t_philo *philo, char *event);

//	to_sleep.c
void	to_sleep(time_t microsec, t_pd  *pdinner);

// utils.c
void	ft_putstr_fd(char *s, int fd);
int		ft_str_isdigit(char *str);
int		chek_str_int_positive(const char *nptr);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
