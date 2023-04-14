/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:00:56 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 11:34:37 by maclara-         ###   ########.fr       */
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
# define INT_MAX	2147483647
# define EATING		"is eating"
# define THINKING	"is thinking"
# define SLEEPING	"is sleeping"
# define TAKEN_FORK	"has taken a fork"
# define DIED		"died"

typedef struct s_philo_dinner t_pd;

typedef struct s_philo
{
	sem_t		*r_fork;
	int			id;
	int			nbr_meals;
	time_t		last_meal;
	pthread_t	checker;
}   t_philo;

typedef struct s_philo_dinner
{
	t_philo		philo;
	pid_t		*pid;
	int			nbr_philo;
	int			nbr_meals;
	time_t		init;
	time_t		time_starv;
	time_t		time_eating;
	time_t		time_sleeping;
	sem_t		*fork;
	sem_t		*msg;
	sem_t		*stop;
	sem_t		*check_meals;
	pthread_t	check;
}   t_pd;

// check_args
int		check_args(int argc, char **argv);

// init_free.c
void	*verify_death(void	*arg);
void	create_sem_fork(t_pd *pdinner);
int		init_semaphores(t_pd *pdinner);
int		init_struct(t_pd *pdinner, char **argv);
void	free_struct(t_pd *pdinner);

// init_thread.c
void	*alert_end_meals(void *arg);
int		init_thread(t_pd *pdinner);

// life.c
void	life(t_pd *pdinner, char *event);
void	to_sleep(time_t microsec, t_pd  *pdinner);
void	*routine(t_pd *pdinner);
int		create_philo(t_pd *pdinner);
void	kill_philo(t_pd *pdinner);

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

// utils2.c
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);

#endif