/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:43:25 by bditte            #+#    #+#             */
/*   Updated: 2021/10/04 10:46:40 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_tabs(t_data *data)
{
	free_philos(data->philos, data->nb_philos);
	free(data->threads);
	free(data->forks);
}

int	malloc_pointers_next(t_data *data)
{
	data->ate_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->ate_lock)
	{
		free(data->all_ate);
		free(data->all_alive);
		free_tabs(data);
		return (ft_print_error("Malloc issue.\n"));
	}
	data->alive_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->alive_lock)
	{
		free(data->ate_lock);
		free(data->all_ate);
		free(data->all_alive);
		free_tabs(data);
		return (ft_print_error("Malloc issue.\n"));
	}
	return (0);
}

int	malloc_pointers(t_data *data)
{
	data->all_alive = malloc(sizeof(int));
	if (!data->all_alive)
	{
		free_tabs(data);
		return (ft_print_error("Malloc issue.\n"));
	}
	*data->all_alive = 1;
	data->all_ate = malloc(sizeof(int));
	if (!data->all_ate)
	{
		free(data->all_alive);
		free_tabs(data);
		return (ft_print_error("Malloc issue.\n"));
	}
	*data->all_ate = 0;
	if (malloc_pointers_next(data))
		return (1);
	return (0);
}

int	init_mutexs(t_data *data)
{
	int	i;

	if (malloc_pointers(data))
		return (1);
	pthread_mutex_init(data->ate_lock, NULL);
	pthread_mutex_init(data->alive_lock, NULL);
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i]->alive_lock = data->alive_lock;
		data->philos[i]->ate_lock = data->ate_lock;
		data->philos[i]->all_alive = data->all_alive;
		data->philos[i]->all_ate = data->all_ate;
		pthread_mutex_init(&data->philos[i]->lock, NULL);
		data->philos[i]->last_eat = data->starting_time;
		data->philos[i]->starting_time = data->starting_time;
	}
	return (0);
}

int	init_threads(t_data *data)
{
	int	i;
	int	ret;

	if (init_mutexs(data))
		return (1);
	i = -1;
	while (++i < data->nb_philos)
	{
		ret = pthread_create(&data->threads[i], NULL, \
			philosopher, (void *)data->philos[i]);
		if (ret)
		{
			pthread_mutex_lock(data->alive_lock);
			*data->all_alive = 0;
			pthread_mutex_unlock(data->alive_lock);
			ret = -1;
			while (++ret <= i)
				pthread_join(data->threads[ret], NULL);
			free_everything(data);
			return (ft_print_error("Thread issue.\n"));
		}
		usleep(100);
	}
	return (0);
}
