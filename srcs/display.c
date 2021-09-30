/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 09:43:14 by bditte            #+#    #+#             */
/*   Updated: 2021/09/30 10:29:16 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char *get_message(int type)
{
	if (type == EATING)
		return ("is eating");
	if (type == DEAD)
		return ("died");
	if (type == SLEEPING)
		return ("is sleeping");
	if (type == THINKING)
		return ("is thinking");
	return ("has taken a fork");
}

int	display_action(t_philo *philo, int type)
{
	static int	displayed;

	if (type == INIT)
	{
		displayed = 0;
		return (0);
	}
	pthread_mutex_lock(&philo->data->display_lock);
	if (!displayed)
	{
		if (type == DEAD)
			displayed = 1;
		printf("%d %d %s\n", get_curr_time(0), philo->i + 1, get_message(type));
	}
	pthread_mutex_unlock(&philo->data->display_lock);
	return (0);
}