/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:39:44 by bditte            #+#    #+#             */
/*   Updated: 2021/09/28 10:00:47 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating(t_philo *philo, pthread_mutex_t *lock, int *forks)
{
	pthread_mutex_lock(lock);
	if ((get_time_in_ms() - philo->last_eat) >= philo->tteat)
	{
		forks[philo->i] = 1;
		forks[(philo->i + 1) % philo->nb_philos] = 1;
		printf("%d %d is done eating\n", \
			get_time_in_ms() - philo->starting_time, philo->i);
		philo->state = DONE_EATING;
		philo->did_eat++;
		pthread_mutex_unlock(lock);
		return (1);
	}
	pthread_mutex_unlock(lock);
	return (0);
}

void	take_forks(t_philo *philo, pthread_mutex_t *lock, int *forks, int nb)
{
	int	curr_time;

	curr_time = get_time_in_ms() - philo->starting_time;
	pthread_mutex_lock(lock);
	if (forks[philo->i] == 1 && philo->state != EATING && \
		((philo->nb_eat && philo->did_eat < philo->nb_eat) || !philo->nb_eat))
	{
		if (forks[(philo->i + 1) % nb] == 1)
		{
			forks[philo->i] = 0;
			forks[(philo->i + 1) % nb] = 0;
			printf("%d %d has taken a fork\n", curr_time, philo->i);
			printf("%d %d has taken a fork\n", curr_time, philo->i);
			printf("%d %d is eating\n", curr_time, philo->i);
			philo->last_eat = get_time_in_ms();
			philo->state = EATING;
		}
	}
	pthread_mutex_unlock(lock); 
}

int	did_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	*philo->all_ate += 1;
	pthread_mutex_unlock(philo->lock);
	philo->did_eat++;
	return (0);
}

int	eat(int i, t_philo *philo, int nb_philo, t_data *data)
{
	static int				*forks;
	static pthread_mutex_t	lock;

	if (i == -1)
	{
		pthread_mutex_init(&lock, NULL);
		forks = data->forks;
		return (0);
	}
	if (philo->nb_eat && philo->did_eat == philo->nb_eat)
		return (did_eat(philo));
	take_forks(philo, &lock, forks, nb_philo);
	if (philo->state == EATING)
	{
		if (is_eating(philo, &lock, forks))
			return (0);
	}
	return (0);
}
