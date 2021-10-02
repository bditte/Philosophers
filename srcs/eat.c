/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:39:44 by bditte            #+#    #+#             */
/*   Updated: 2021/10/01 10:39:21 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->fork_left]);
	pthread_mutex_unlock(&philo->data->forks[philo->fork_right]);
	philo->did_eat++;
	if (philo->data->nb_eat && philo->did_eat == philo->data->nb_eat)
	{
		pthread_mutex_lock(philo->ate_lock);
		(*philo->all_ate)++;
		pthread_mutex_unlock(philo->ate_lock);
	}
	return (0);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
	display_action(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
	display_action(philo, TAKE_FORK);
	display_action(philo, EATING);
}

int	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = get_time_in_ms();
	philo->state = EATING;
	usleep(philo->data->tteat * 1000);
	drop_forks(philo);
	philo->state = SLEEPING;
	pthread_mutex_unlock(&philo->lock);
	return (0);
}
