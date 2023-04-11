/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:16:46 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/11 08:16:43 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <semaphore.h>
# include <pthread.h>

typedef struct  s_philo
{
    size_t          id;
    pthread_t       thread;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *r_fork;
    time_t          init_last_meal;
    size_t          nbr_meals;
    bool            stop;
    t_pd            *pd;
}   t_philo;

typedef struct s_philo_dinner
{
    t_philo         *philo;
    size_t          nbr_philo;
    time_t          time_to_starv;
    time_t          time_eating;
    time_t          time_sleeping;
    size_t          nbr_meals;
    pthread_mutex_t *fork;
    pthread_mutex_t msg;
    bool            stop;
}   s_pd;

// check_args.c
int	check_args(int argc, char **argv);


// utils.c
void	ft_putstr_fd(char *s, int fd);
int     ft_str_isdigit(char *str);


#endif
