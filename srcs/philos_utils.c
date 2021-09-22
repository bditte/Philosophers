/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:07:54 by bditte            #+#    #+#             */
/*   Updated: 2021/09/22 15:43:14 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(t_philo *philo, int time)
{
	while (time / 10 >= 1)
	{
		usleep(10 * 1000);
		time -= 10;
		if (is_dead(philo))
			return (1);
	}
	usleep((time % 10) * 1000);
	return (0);
}

int	is_dead(t_philo *philo)
{
	int	curr_time;

	curr_time = get_time_in_ms();
	if (curr_time - philo->last_eat > philo->ttdie)
	{
		philo->state = DEAD;
		printf("%d %d died\n", curr_time - philo->starting_time, philo->i);
		return (1);
	}
	return (0);
}
