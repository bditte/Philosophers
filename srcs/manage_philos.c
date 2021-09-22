/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 13:57:10 by bditte            #+#    #+#             */
/*   Updated: 2021/09/22 15:44:12 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		handle_forks(int i, t_philo *philo, int nb_philo)
{
	static int				*forks;
	int						curr_time;
	static pthread_mutex_t	lock;
	if (i == -1)
	{
		pthread_mutex_init(&lock, NULL);
		forks = malloc(sizeof(int) * nb_philo);
		if (!forks)
			return (-1);
		while (++i < nb_philo)
			forks[i] = 1;
		return (0);
	}
	pthread_mutex_lock(&lock);
	curr_time = get_time_in_ms() - philo->starting_time;
	if (forks[i] == 1 && philo->state != EATING)
	{
		if (forks[(i + 1) % nb_philo] == 1)
		{
			forks[i] = 0;
			forks[(i + 1) % nb_philo] = 0;
			printf("%d %d has taken fork %d\n", curr_time, i, i);
			printf("%d %d has taken fork %d\n", curr_time, i, (i + 1) % nb_philo);
			philo->last_eat = get_time_in_ms();
			philo->state = EATING;
		}

	}
	pthread_mutex_unlock(&lock);
	if (philo->state == EATING)
	{
		pthread_mutex_lock(&lock);
		if ((get_time_in_ms() - philo->last_eat) >= philo->tteat)
		{
			forks[i] = 1;
			forks[(i + 1) % nb_philo] = 1;
			printf("%d %d is done eating\n", get_time_in_ms() - philo->starting_time, i);
			philo->state = DONE_EATING;	
			pthread_mutex_unlock(&lock);
			return (0);
		}
		pthread_mutex_unlock(&lock);
	}
	return (0);

}

void	*philosopher(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (is_dead(philo))
			return (NULL);
		handle_forks(philo->i, philo, philo->nb_philos);
		if (philo->state == DONE_EATING)
		{
			printf("%d %d is sleeping\n", get_time_in_ms() - philo->starting_time, philo->i);
			if (ft_sleep(philo, philo->ttsleep * 1000))
				return (NULL);
			if (is_dead(philo))
				return (NULL);
			printf("%d %d is thinking\n", get_time_in_ms() - philo->starting_time, philo->i);
			philo->state = THINKING;
		}
	}//printf("philo number %d fork 1 %d\n", philo->i, philo->forks[0]);
	return (data);
}

int	manage_philos(t_data *data)
{
	int		i;
	int		ret;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	handle_forks(-1, NULL, data->nb_philos);
	data->starting_time = get_time_in_ms();
	i = -1;
	while (++i < data->nb_philos)
	{
		//data->philos[i]->lock = mutex;
		data->philos[i]->last_eat = data->starting_time;
		data->philos[i]->starting_time = data->starting_time;
		ret = pthread_create(&data->threads[i], NULL, philosopher, (void *)data->philos[i]);
	}
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_join(data->threads[i], NULL);
	}
	return (0);
}