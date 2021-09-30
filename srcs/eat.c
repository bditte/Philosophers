/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:39:44 by bditte            #+#    #+#             */
/*   Updated: 2021/09/30 13:54:24 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
int	did_eat(t_philo *philo)
{
	if ((philo->did_eat == philo->nb_eat) && philo->nb_eat)
	{
		pthread_mutex_lock(philo->lock);
		*philo->all_ate += 1;
		pthread_mutex_unlock(philo->lock);
	}
	return (0);
}*/

int	drop_forks(t_philo *philo)
{
	/*	pthread_mutex_lock(lock);
	if ((get_time_in_ms() - philo->last_eat) >= philo->data->tteat)
	{
		printf("next fork%d\n", (philo->i +1)% philo->data->nb_philos);
		forks[philo->i] = 1;
		forks[(philo->i + 1) % philo->data->nb_philos] = 1;
		display_action(philo, DONE_EATING);
		philo->state = DONE_EATING;
		philo->did_eat++;
		pthread_mutex_unlock(lock);
		did_eat(philo);
		return (1);
	}
	pthread_mutex_unlock(lock);
	*/
	pthread_mutex_unlock(&philo->data->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_right]);
	return (0);
}

void	take_forks(t_philo *philo)
{
	/*int	curr_time;

	curr_time = get_time_in_ms() - philo->starting_time;
	pthread_mutex_lock(lock);
	if (forks[philo->i] == 1 && philo->state != EATING)
	{
		if (forks[(philo->i + 1) % nb] == 1)
		{
			forks[philo->i] = 0;
			forks[(philo->i + 1) % nb] = 0;
			display_action(philo, TAKE_FORK);
			display_action(philo, TAKE_FORK);
			display_action(philo, EATING);
			philo->last_eat = get_time_in_ms();
			philo->state = EATING;
		}
	}
	pthread_mutex_unlock(lock);*/
	pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
	display_action(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
	display_action(philo, TAKE_FORK);
	display_action(philo, EATING);
}

int	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->lock);
	philo->last_eat = get_time_in_ms();
	philo->state = EATING;
	//printf("Philo %d here at %d\n", philo->i, get_curr_time(0));
	usleep(philo->data->tteat * 1000);
	//printf("Philo %d here\n", philo->i);
	drop_forks(philo);
	philo->state = SLEEPING;
	pthread_mutex_unlock(philo->lock);
	return (0);
}
