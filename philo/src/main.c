/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:49 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/17 14:12:27 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_events(t_philo *philo, char *event)
{
	time_t	time;

	pthread_mutex_lock(&philo->pdinner->msg);
	time = get_time() - philo->pdinner->init;
	printf("%ld %d %s\n", time, philo->id, event);
	pthread_mutex_unlock(&philo->pdinner->msg);
}

void	only_one(char **argv)
{
	int	life_time;

	life_time = ft_atoi(argv[2]);
	printf("0 1 %s \n", TAKEN_FORK);
	usleep(life_time * 1000);
	printf("%d 1 died\n", life_time);
}

int	main(int argc, char **argv)
{
	t_pd	*pdinner;

	if (!check_args(argc, argv))
		return (-1);
	if (ft_atoi(argv[1]) == 1)
		return (only_one(argv), -3);
	pdinner = (t_pd *) ft_calloc(1, sizeof(t_pd));
	if (!init_struct(pdinner, argv))
		return (-1);
	if (!init_mutex(pdinner))
		return (-4);
	init_philo(pdinner);
	if (!philos_threads_born(pdinner))
	{
		free_struct(pdinner);
		free(pdinner);
		return (-1);
	}
	free_struct(pdinner);
	return (0);
}
