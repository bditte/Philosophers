/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:57:10 by bditte            #+#    #+#             */
/*   Updated: 2021/10/03 17:58:36 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	int	i;

	while (1)
	{
		/*pthread_mutex_lock(data->alive_lock);
		if (!(*data->all_alive))
		{
			pthread_mutex_unlock(data->alive_lock);
			return (1);
		}
		pthread_mutex_unlock(data->alive_lock);
		pthread_mutex_lock(data->ate_lock);*/
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
				return (0);
			}
			pthread_mutex_unlock(&data->philos[i]->lock);
		}
		if (data->nb_eat && (*data->all_ate == data->nb_philos))
		{
			pthread_mutex_unlock(data->ate_lock);
			return (1);
		}
		pthread_mutex_unlock(data->ate_lock);
	}
	return (0);
}

int	check_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->ate_lock);
	if (philo->data->nb_eat && *philo->all_ate == philo->data->nb_philos)
	{
		pthread_mutex_unlock(philo->ate_lock);
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(philo->ate_lock);
	return (0);
}
/*
void	*checker(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (check_eat(philo))
			return (NULL);
		if (philo->state != EATING)
		{
			if (get_time_in_ms() - philo->last_eat >= philo->data->ttdie)
			{
				display_action(philo, DEAD);
				pthread_mutex_lock(philo->alive_lock);
				*philo->all_alive = 0;
				philo->state = DEAD;
				pthread_mutex_unlock(philo->alive_lock);
				pthread_mutex_unlock(&philo->lock);
				return (NULL);
			}
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(10);
	}
}*/

void	*philosopher(void *data)
{
	t_philo		*philo;
	//pthread_t	thread;

	/*pthread_create(&thread, NULL, checker, data);
	pthread_detach(thread);*/
	philo = (t_philo *)data;
	while (1)
	{
		if (is_dead(philo) || all_ate(philo))
			return (NULL);
		if (eat(philo))
		{
			usleep(philo->data->ttsleep * 1000);
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
