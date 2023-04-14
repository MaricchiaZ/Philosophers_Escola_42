/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:51 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/14 12:05:28 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_event(t_pd *pdinner, t_philo *philo, char *event)
{
	time_t	time;
	
	time = get_time() - pdinner->init;
	printf("%ld %d %s\n", time, philo->id, event);
}

void	only_one(char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		printf("0 1 taken a fork\n");
		usleep(1000 * ft_atoi(argv[2]));
		printf("%s 1 died\n", argv[2]);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv)
{
	t_pd	*pdinner;

	if (!check_args(argc, argv))
		return (-1);
	if (ft_atoi(argv[1]) == 1)
		return (only_one(argv), 0);
	pdinner = (t_pd *) ft_calloc(1, sizeof(t_pd)); // alocamos a struct e iniciamos td zerado
	if (!init_struct(pdinner, argv))
		return (-2);
	if (!create_philo(pdinner))
		return (-3);
	kill_philo(pdinner);
	free_struct(pdinner);
	return (0); 
}
