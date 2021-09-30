/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:57:10 by bditte            #+#    #+#             */
/*   Updated: 2021/09/30 13:57:02 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(data->philos[0]->alive_lock);
		if (!(*data->all_alive) )//|| *all_ate == nb)
		{
			pthread_mutex_unlock(data->philos[0]->alive_lock);
			return (1);
		}
		pthread_mutex_unlock(data->philos[0]->alive_lock);
	}
	return (0);
}

void	*checker(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(philo->lock);
		//printf("Here at %d\n", get_curr_time(0));
		if (philo->state != EATING)
		{
			//printf("Here at %d last eat %d\n", get_curr_time(0), philo->last_eat);
	//		if (philo->state == SLEEPING)
	//			printf("PHILO %d is sleeping last meal %d\n", philo->i, philo->last_eat);
			if (get_time_in_ms() - philo->last_eat >= philo->data->ttdie)
			{
				display_action(philo, DEAD);
				pthread_mutex_lock(philo->alive_lock);
				*philo->all_alive = 0;
				philo->state = DEAD;
				pthread_mutex_unlock(philo->alive_lock);
				pthread_mutex_unlock(philo->lock);
				return (NULL);
			}
		}
		pthread_mutex_unlock(philo->lock);
		usleep(1000);
	}
}

void	*philosopher(void *data)
{
	t_philo		*philo;
	pthread_t	thread;

	pthread_create(&thread, NULL, checker, data);
	//pthread_detach(thread);
	philo = (t_philo *)data;
	while (1)
	{
		if (is_dead(philo)) //check all ate
			return (NULL);
		eat(philo);
		display_action(philo, SLEEPING);
		usleep(philo->data->ttsleep * 1000);
		/*if (ft_sleep(philo, philo->data->ttsleep))
			return (NULL);*/
		display_action(philo, THINKING);
		philo->state = THINKING;
	}
	return (data);
}

int	manage_philos(t_data *data)
{
	int		i;

	//eat(-1, NULL, data->nb_philos, data);
	get_curr_time(1);
	display_action(NULL, INIT);
	pthread_mutex_init(&data->display_lock, NULL);
	data->starting_time = get_time_in_ms();
	init_threads(data);
	if (check_death(data))
	{
		free(data->all_alive);
		free(data->all_ate);
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_unlock(&data->forks[i]);
			pthread_join(data->threads[i], NULL);
		}
	}
	
	return (0);
}
