/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:57:10 by bditte            #+#    #+#             */
/*   Updated: 2021/10/04 10:49:11 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_data *data)
{
	pthread_mutex_lock(data->ate_lock);
	if (data->nb_eat && (*data->all_ate == data->nb_philos))
	{
		pthread_mutex_unlock(data->ate_lock);
		return (1);
	}
	pthread_mutex_unlock(data->ate_lock);
	return (0);
}


int	check_death(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_lock(&data->philos[i]->lock);
			if (get_time_in_ms() - data->philos[i]->last_eat >= data->ttdie)
			{
				display_action(i, DEAD, &data->display_lock);
				pthread_mutex_lock(data->alive_lock);
				*data->all_alive = 0;
				pthread_mutex_unlock(data->alive_lock);
				pthread_mutex_unlock(&data->philos[i]->lock);
				return (1);
			}
			pthread_mutex_unlock(&data->philos[i]->lock);
		}
		if (check_eat(data))
			return (1);
	}
	return (0);
}

void	*philosopher(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->i % 2)
		usleep(15000);
	while (1)
	{
		if (is_dead(philo) || all_ate(philo))
			return (NULL);
		if (eat(philo))
		{
			ft_sleep(philo->data->ttsleep);
			display_action(philo->i, THINKING, &philo->data->display_lock);
			philo->state = THINKING;
		}
	}
	return (data);
}

int	manage_philos(t_data *data)
{
	int		i;

	get_curr_time(1);
	display_action(0, INIT, NULL);
	pthread_mutex_init(&data->display_lock, NULL);
	data->starting_time = get_time_in_ms();
	if (init_threads(data))
		return (1);
	if (check_death(data))
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			pthread_mutex_unlock(&data->forks[i]);
			pthread_join(data->threads[i], NULL);
		}
	}
	return (0);
}
