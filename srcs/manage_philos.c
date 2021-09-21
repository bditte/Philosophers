/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:57:10 by bditte            #+#    #+#             */
/*   Updated: 2021/09/21 15:13:38 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(t_philo philo, t_data *data)
{
	(void)philo;
	(void)data;
	return NULL;
}

void	*ft_test(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	printf("philo number %d fork 1 %d\n", philo->i, philo->forks[0]);
	return (data);
}

int	manage_philos(t_data *data)
{
	int		i;
	int		ret;

	data->starting_time = get_time_in_ms();
	i = -1;
	while (++i < data->nb_philos)
	{
		printf("fork 1 %d\n", data->forks[0]);
		ret = pthread_create(&data->threads[i], NULL, ft_test, (void *)data->philos[i]);
	}
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_join(data->threads[i], NULL);
	}
	return (0);
}