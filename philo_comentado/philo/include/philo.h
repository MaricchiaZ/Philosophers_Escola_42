/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:16:46 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/23 11:21:43 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>

# define STOP		1
# define CONTINUE	0
# define FALSE		0
# define TRUE		1
# define INT_MAX	2147483647 // pra conferir se os argumentos ultrapassam o int max
# define EATING		"is eating" // mensagem que colocamos no terminal conforme os filósofos são fazendo as atividades
# define THINKING	"is thinking" // ''
# define SLEEPING	"is sleeping" // ''
# define TAKEN_FORK	"has taken a fork" // ''

typedef struct s_philo_dinner   t_pd;

typedef struct  s_philo
{
	int				id; // o número do filósofo à mesa
	pthread_t		thread; // a tread dele
	pthread_mutex_t	*r_fork; // o garfo direito que é o que ele traz de casa
	pthread_mutex_t	*l_fork; // o garfo esquerdo (que ele pega emprestado do filósofo ao lado)
	time_t			last_meal; // que horas foi a última vez que ele comeu
	int				nbr_meals; // o número de refeições que ele fez
	int				stop; // flag para avisar que deve parar a simulação
	t_pd			*pdinner; // ponteiro para a "mesa de jantar"
}   t_philo;

typedef struct s_philo_dinner
{
	t_philo			*philo; // ponteiro pro filo
	int				nbr_philo; // número total de filósofos que vieram para o jantar
	time_t			time_to_starv; // tempo que eles aguentam até morrer de fome (starv = inanição em inglês)
	time_t			time_eating; // tempo que eles gastam dormindo
	time_t			time_sleeping; // tempo que eles gastam comendo
	int				nbr_meals; // número de refeições que eles devem fazer
	pthread_mutex_t	*fork; // mutex pra travar o acesso aos garfos
	pthread_mutex_t	msg; // mutex pra travar o acesso a escrita de mensagens no terminal (e não misturar uma mensagem com a outra)
	pthread_mutex_t	mstop; // mutex pra travar o acesso á flag de parada
	time_t			init; // salvamos o horário que começa o jantar
	int				stop; // flag de parada
}   s_pd;

// check_args.c
int		check_args(int argc, char **argv);

// init_free.c
void	init_philo(t_pd	*pdinner);
int		init_struct(t_pd *pdinner, char **argv);
int		init_mutex(t_pd *pdinner);
void	free_struct(t_pd *pdinner);

// life_philos.c
int		life(t_philo *philo, char *event);
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

// utils2.c
int		ft_strcmp(char *s1, char *s2);

#endif
