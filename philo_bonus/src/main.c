/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 20:59:51 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/13 11:03:42 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void    only_one(char **argv)
{
    pid_t   pid;
    long    init;

    pid = fork();
    if (pid == 0)
    {
        init = get_time();
        printf("0   1 taken a fork\n");
        usleep(1000 * ft_atoi(argv[2]));
        printf("%s  1 died");
    }
    waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv)
{
	t_pdinner   pdinner;

    if (!check_args(argc, argv))
        return (1);
    if (ft_atoi(argv[1] == 1))
        return (one_philo(argv), 0);
    if (!init_struct(&pdinner, argv))
        return (2);
    if (!create_philo(&pdinner))
        return (3);
    return (0);
}
