/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:43:25 by bditte            #+#    #+#             */
/*   Updated: 2021/10/01 10:50:14 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexs(t_data *data)
{
	int				i;
	//pthread_mutex_t	ate_lock;
	//pthread_mutex_t	alive_lock;

	
	data->all_alive = malloc(sizeof(int));
	*data->all_alive = 1;
	data->all_ate = malloc(sizeof(int));
	*data->all_ate = 0;
	data->ate_lock = malloc(sizeof(pthread_mutex_t));
	data->alive_lock = malloc(sizeof(pthread_mutex_t));
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

	init_mutexs(data);
	i = -1;
	while (++i < data->nb_philos)
	{
		ret = pthread_create(&data->threads[i], NULL, \
			philosopher, (void *)data->philos[i]);
		if (ret)
			printf("thread error\n");
		usleep(100);
	}
	return (0);
}
