/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:00:56 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 16:25:41 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <wait.h>

# define STOP		1
# define CONTINUE	0
# define FALSE		0
# define TRUE		1
# define INT_MAX	2147483647
# define EATING		"is eating"
# define THINKING	"is thinking"
# define SLEEPING	"is sleeping"
# define TAKEN_FORK	"has taken a fork"
# define DIED		"died"

typedef struct s_philo_dinner	t_pd;
typedef struct s_philo			t_philo;

typedef struct s_philo
{
	int				id;
	int				nbr_meals;
	time_t			last_meal;
	pid_t			pid;
	t_philo			*next;
	t_philo			*prev;
	t_pd			*pdinner;
}	t_philo;

typedef struct s_philo_dinner
{
	t_philo	*philo;
	time_t	init;
	int		nbr_philo;
	int		nbr_meals;
	int		time_starv;
	int		time_eating;
	int		time_sleeping;
	int		stop;
	sem_t	*fork;
	sem_t	*msg;
}	t_pd;

// check_args
int		check_args(int argc, char **argv);

// init_free.c
void	create_philo_process(t_pd *pdinner);
void	init_philo_and_sem(t_pd *pdinner);
void	init_struct(t_pd *pdinner, char **argv);
void	free_struct(t_pd *pdinner);

// life.c
void	*life(t_philo *aux);
void	eat(t_philo *philo);
void	to_sleep(t_philo *philo);
void	think(t_philo *philo);
void	verify_death(int time, t_philo *philo);

// main.c
time_t	get_time(void);
void	only_one(char **argv);
void	print_event(t_pd *pdinner, t_philo *philo, char *event);

// utils.c
void	ft_putstr_fd(char *s, int fd);
int		ft_str_isdigit(char *str);
int		chek_str_int_positive(const char *nptr);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

// wait_process.c
void	wait_process(t_pd *pdinner);

#endif