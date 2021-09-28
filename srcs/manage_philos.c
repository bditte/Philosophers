/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:57:10 by bditte            #+#    #+#             */
/*   Updated: 2021/09/28 14:28:51 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(pthread_mutex_t *mutex, int *all_alive, int *all_ate, int nb)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (!(*all_alive) || *all_ate == nb)
		{
			pthread_mutex_unlock(mutex);
			return (1);
		}
		pthread_mutex_unlock(mutex);
	}
	return (0);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (is_dead(philo))
			return (NULL);
		eat(philo->i, philo, philo->nb_philos, NULL);
		if (all_ate(philo) && philo->state != EATING)
			return (NULL);
		if (philo->state == DONE_EATING)
		{
			if (all_ate(philo))
				return (NULL);
			printf("%d %d is sleeping\n", get_time_in_ms() - \
				philo->starting_time, philo->i + 1);
			if (ft_sleep(philo, philo->ttsleep))
				return (NULL);
			printf("%d %d is thinking\n", get_time_in_ms() - \
				philo->starting_time, philo->i + 1);
			philo->state = THINKING;
		}
	}
	return (data);
}

int	manage_philos(t_data *data)
{
	int		i;

	eat(-1, NULL, data->nb_philos, data);
	data->starting_time = get_time_in_ms();
	init_threads(data);
	if (check_death(&data->mutex, data->all_alive, \
		data->all_ate, data->nb_philos))
	{
		free(data->all_alive);
		free(data->all_ate);
		i = -1;
		while (++i < data->nb_philos)
			pthread_join(data->threads[i], NULL);
	}
	return (0);
}
