/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:43:25 by bditte            #+#    #+#             */
/*   Updated: 2021/10/02 10:44:21 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	malloc_pointers(t_data *data)
{
	data->all_alive = malloc(sizeof(int));
	if (!data->all_alive)
		return (ft_print_error("Malloc issue.\n"));
	*data->all_alive = 1;
	data->all_ate = malloc(sizeof(int));
	if (!data->all_ate)
		return (ft_print_error("Malloc issue.\n"));
	*data->all_ate = 0;
	data->ate_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->ate_lock)
		return (ft_print_error("Malloc issue.\n"));
	data->alive_lock = malloc(sizeof(pthread_mutex_t));
	if (!data->alive_lock)
		return (ft_print_error("Malloc issue.\n"));
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
			return (ft_print_error("Thread issue.\n"));
		usleep(100);
	}
	return (0);
}
