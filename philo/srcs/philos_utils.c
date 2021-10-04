/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:07:54 by bditte            #+#    #+#             */
/*   Updated: 2021/10/04 10:45:53 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(int time)
{
	int	start_time;

	start_time = get_curr_time(0);
	while (get_curr_time(0) - start_time < time)
		usleep(1000);
	return (0);
}

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
	pthread_mutex_lock(philo->alive_lock);
	if (!(*philo->all_alive))
	{
		pthread_mutex_unlock(philo->alive_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->alive_lock);
	if (philo->state == EATING)
		return (0);
	return (0);
}
