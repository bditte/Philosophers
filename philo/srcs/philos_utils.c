/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:07:54 by bditte            #+#    #+#             */
/*   Updated: 2021/10/03 18:00:46 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo, int time)
{
	int	i;

	(void)philo;
	i = 0;
	time *= 1000;
	while (i < time && time - i > 10000)
	{
		usleep(10000);
		i += 10000;
	}
	usleep(time - i);
	return (0);
}
/*
int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(philo->alive_lock);
	if (!(*philo->all_alive))
	{
		pthread_mutex_unlock(philo->alive_lock);
		return (1);
	}
	*philo->all_alive = 0;
	pthread_mutex_unlock(philo->alive_lock);
	philo->state = DEAD;
	display_action(philo, DEAD);
	return (1);
}*/

int	all_ate(t_philo *philo)
{
	pthread_mutex_lock(philo->ate_lock);
	if (*philo->all_ate == philo->data->nb_philos)
	{
		pthread_mutex_unlock(philo->ate_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->ate_lock);
	return (0);
}

int	is_dead(t_philo *philo)
{
	//int	curr_time;

	pthread_mutex_lock(philo->alive_lock);
	if (!(*philo->all_alive))
	{
		pthread_mutex_unlock(philo->alive_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->alive_lock);
	if (philo->state == EATING)
		return (0);
/*	curr_time = get_time_in_ms();
	if (curr_time - philo->last_eat > philo->data->ttdie)
		return (philo_died(philo));*/
	return (0);
}