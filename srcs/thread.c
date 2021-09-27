/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:43:25 by bditte            #+#    #+#             */
/*   Updated: 2021/09/27 10:17:30 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_data *data)
{
	int	i;
	int	ret;

	data->all_alive = malloc(sizeof(int));
	*data->all_alive = 1;
	pthread_mutex_init(&data->mutex, NULL);
	i = -1;
	while (++i < data->nb_philos)
	{
		data->philos[i]->all_alive = data->all_alive;
		data->philos[i]->lock = &data->mutex;
		data->philos[i]->last_eat = data->starting_time;
		data->philos[i]->starting_time = data->starting_time;
		ret = pthread_create(&data->threads[i], NULL, \
			philosopher, (void *)data->philos[i]);
		if (ret)
			printf("thread error\n");
	}
	return (0);
}
