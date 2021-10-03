/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:39:44 by bditte            #+#    #+#             */
/*   Updated: 2021/10/03 18:05:24 by bditte           ###   ########.fr       */
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

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->fork_left]);
	display_action(philo->i, TAKE_FORK, &philo->data->display_lock);
	if (philo->fork_left == philo->fork_right)
		return (0);
	pthread_mutex_lock(&philo->data->forks[philo->fork_right]);
	display_action(philo->i, TAKE_FORK, &philo->data->display_lock);
	display_action(philo->i, EATING, &philo->data->display_lock);
	return (1);
}

int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = get_time_in_ms();
	pthread_mutex_unlock(&philo->lock);
	philo->state = EATING;
	usleep(philo->data->tteat * 1000);
	drop_forks(philo);
	display_action(philo->i, SLEEPING, &philo->data->display_lock);
	philo->state = SLEEPING;
	return (1);
}
