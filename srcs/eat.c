/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:39:44 by bditte            #+#    #+#             */
/*   Updated: 2021/09/24 16:47:24 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(pthread_mutex_t *lock, int *forks, int nb_philo)
{
	int	i;

	i = -1;
	pthread_mutex_init(lock, NULL);
	forks = malloc(sizeof(int) * nb_philo);
	if (!forks)
		return (-1);
	while (++i < nb_philo)
		forks[i] = 1;
	return (0);
}

int	is_eating(t_philo *philo, pthread_mutex_t *lock, int *forks)
{
	pthread_mutex_lock(lock);
	if ((get_time_in_ms() - philo->last_eat) >= philo->tteat)
	{
		forks[philo->i] = 1;
		forks[(philo->i + 1) % philo->nb_philos] = 1;
		printf("%d %d is done eating\n", get_time_in_ms() - philo->starting_time, i);
		philo->state = DONE_EATING;	
		pthread_mutex_unlock(&lock);
		return (1);
	}
	pthread_mutex_unlock(&lock);
	return (0);
}

int	eat(int i, t_philo *philo, int nb_philo)
{
	static int				*forks;
	int						curr_time;
	static pthread_mutex_t	lock;
	if (i == -1)
		return (init_forks, &lock, forks, nb_philo);
	curr_time = get_time_in_ms() - philo->starting_time;
	pthread_mutex_lock(&lock);
	if (forks[i] == 1 && philo->state != EATING && (philo->nb_eat && philo->did_eat < philo->nb_eat))
	{
		if (forks[(i + 1) % nb_philo] == 1)
		{
			forks[i] = 0;
			forks[(i + 1) % nb_philo] = 0;
			printf("%d %d has taken fork %d\n", curr_time, i, i);
			printf("%d %d has taken fork %d\n", curr_time, i, (i + 1) % nb_philo);
			printf("%d %d is eating\n", curr_time, i);
			philo->last_eat = get_time_in_ms();
			philo->state = EATING;
		}

	}
	pthread_mutex_unlock(&lock);
	if (philo->state == EATING)
	{
		if (is_eating(philo, &lock, forks))
			return (0);
	}
	return (0);
}
