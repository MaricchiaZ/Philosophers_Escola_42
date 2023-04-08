/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:37:43 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/08 10:14:11 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// CodeVault: https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <pthread.h>

void    *routine() 
{
    prinf("Test from threads\n")
}

int main(int argc, char **argv)
{
    pthread_t t1; // variável que vai receber o API e informações sobre a thread

    pthread_create(&t1, NULL, &routine, NULL); // &t1 - thread que será criada/inicializada, NULL - configurações adicionais, se for null criará no modo padrão, &routine a função que vai rodar qnd a thread for criada, NULL o que fazer após criar a thread.
    return (0);
}