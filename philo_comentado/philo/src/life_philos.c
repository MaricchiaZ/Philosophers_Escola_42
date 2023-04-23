/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maclara- <maclara-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:46:12 by maclara-          #+#    #+#             */
/*   Updated: 2023/04/23 12:52:53 by maclara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life(t_philo *philo, char *event) // função auxiliar da rotina, que coordena as atividades da vida do filósofo
{
	pthread_mutex_lock(&philo->pdinner->mstop); // travamos o uso da variável stop
	if (philo->pdinner->stop) // se o filósofo que está vivendo tem a flag para parar
	{
		pthread_mutex_unlock(&philo->pdinner->mstop); // destravamos o uso da variável stop
		return (STOP); // retornamos a ordem de parada da simulação
	}
	pthread_mutex_unlock(&philo->pdinner->mstop); // destravamos o uso da variável stop
    if (!ft_strcmp(event, EATING)) // se o envento for comer
    {
        print_events(philo, EATING); // printamos a mendagem de que o filósofo vai comer
        philo->last_meal = get_time(); // atualizamos o tempo da última refeição
        philo->nbr_meals++; // atualizamos o número de refeições que ele fez
        if (philo->nbr_meals == philo->pdinner->nbr_meals) // se atingiu o número máximo de refeições que ele deve fazer
            check_limit_meals(philo->pdinner); //checamos o número de refeições de todos
    }
	else // se o evento não for COMER, pode ser DORMIR OU PENSAR
    	print_events(philo, event); // então printamos a ação do filósofo
    return (CONTINUE); // e continumaos a simulação
}

void	*routine(void *arg) //função essencial da pthread_create, referente a rotina do filósofo
{
	t_philo	*philo; // jeito de dizer que essa função é referente a um filósofo

	philo = arg; // o filósofo passado como argumento para a função essencial da pthread_create
	if (philo->id %2 == 0) // os filósofos de número par, esperam um pouquinho para iniciar, isso evita que cada um
	// pegue seu garfo na mão e fique todos com apenas um garfo e ninguém possa comer - evitando assim que esses 
	//filósofos geniais morram de fome ....
		to_sleep(philo->pdinner->time_eating / 2, philo->pdinner); // vão esperar um pouco
	while (philo->stop == FALSE) // enquanto não tiver que parar a simulação
	{
		pthread_mutex_lock(philo->r_fork); // travamos o garfo diretito
		philo->stop = life(philo, TAKEN_FORK); // o filósofo pega o garfo direito (retornamos o valor da ação STOP ou 
		// CONTINUE para ficarmos verificando se está td ok)
		pthread_mutex_lock(philo->l_fork); // travamos o garfo esquerdo
		philo->stop = life(philo, TAKEN_FORK); // o filósofo pega o garfo esquerdo
		philo->stop = life(philo, EATING); // o filósofo come
		to_sleep(philo->pdinner->time_eating, philo->pdinner); // colocamos o filófoso em espera (pra comer)
		philo->stop = life(philo, SLEEPING); // o fiósofo dorme após comer 
		pthread_mutex_unlock(philo->r_fork); // destravamos o garfo diretito
		pthread_mutex_unlock(philo->l_fork); // destravamos o garfo esquerdo
		to_sleep(philo->pdinner->time_sleeping, philo->pdinner);
		philo->stop = life(philo, THINKING); // colocamos o filófoso em espera (pra dormir)
	}
	//if (philo->r_fork == philo->l_fork) // se o garfo esquerdo for o mesmo que o direito (caso tenha ficado um filo só)
		//pthread_mutex_unlock(philo->l_fork); // destravamos o garfo
	return (NULL); // retornamos null
}

int check_limit_meals(t_pd *pdinner) // conferimos se todos os filósofos atingiram o número máximo de refeições
{
	int	i;

	i = 0;
	while (i < pdinner->nbr_philo) // enquanto não olharmos todos os filósofos
	{
		if (pdinner->philo[i].nbr_meals < pdinner->nbr_meals) // se o número de refeições que ele fez for menor do
		// que o número de refeições que ele deve fazer
			return (FALSE); // não deve parar a rotina
		i++;
	}
	pdinner->stop = TRUE; // se não entrar no if, aí atingiu o número de refeições e paramos a rotina
	return (TRUE); // retornamos que é VERDADE que atingiu o número máximo de refeições
}

void	verify_death(t_pd *pdinner) // verifica se tds os filósofos estão vivos
{
	int	i; // contador pra percorrer os filos
	time_t	time; // tempo atual

	while (1) // ciclo eterno
	{
		i = 0; //
		time = get_time(); // conferimos o tempo de agora
		while (i < pdinner->nbr_philo) // enquanto nao passarmos por todos os filos
		{
			if (time - pdinner->philo[i].last_meal >= pdinner->time_to_starv) // vemos se o tempo transcorrido desde a última refeição é maior ou igual ao tempo pro filo morrer de inanição
			{
				pthread_mutex_lock(&pdinner->mstop);
				print_events(&pdinner->philo[i], "died"); //printamos a morte do filo
				pdinner->stop = TRUE; // vamos parar o programa
				pthread_mutex_unlock(&pdinner->mstop);
				break; // saímos do while
			}
			i++; // vamos pro próximo filósofo
		}
		usleep(100);  // para dar tempo do aviso de parada ser visto por todas as threads
		if (pdinner->stop == TRUE) // se temos o aviso pra parar...
			return ; // retornamos
	}
}

int	philos_threads_born(t_pd *pdinner) // iniciamos a thread que cada filósofo representa
{
	int	i;

	i = 0;
	pdinner->init = get_time(); // anotamos o horário que inciamos o programa
	while (i < pdinner->nbr_philo) // enquanto n passarmos por todos os filósofos
	{
		pdinner->philo[i].last_meal = pdinner->init; // o tempo de início é a "última refeição feita"
		if (pthread_create(&pdinner->philo[i].thread, NULL, &routine, &pdinner->philo[i])) // criamos a thread pra cada
		// filósofo
		{
			ft_putstr_fd("Pthread_create error\n", 2); // se der erro na criação da thread, avisamos o erro
			pthread_mutex_lock(&pdinner->mstop); // travamos a mutex do stop
			pdinner->stop = TRUE; // ativamos o stop
			pthread_mutex_unlock(&pdinner->mstop);  // destravamos a mutex do stop
			return (0); // retornamos FALSE ou o erro
		}
		i++; // percorremos todos os filósofos
	}
	verify_death(pdinner); // verificamos se alguém morreu enquanto inicialiamos as coisas
	return (1); // retornamos TRUE ou "ok, tudo certo"
}
