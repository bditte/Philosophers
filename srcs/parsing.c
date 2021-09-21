/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:01:52 by bditte            #+#    #+#             */
/*   Updated: 2021/09/21 15:06:30 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philos(int nb_philos, int *forks)
{
	t_philo **res;
	int		i;
	res = malloc(sizeof(t_philo *) * (nb_philos + 1));
	if (!res)
		return (NULL);
	res[nb_philos] = NULL;
	i = -1;
	while (++i < nb_philos)
	{
		res[i] = malloc(sizeof(res[i]));
		if (!res[i])
			return (NULL);
		res[i]->i = i + 1;
		res[i]->last_eat = 0;
		res[i]->state = -1;
		res[i]->forks = malloc(sizeof(int *));
		res[i]->forks = forks;
	}
	return (res);
}

int	*create_forks(int nb)
{
	int	*res;
	int	i;

	res = malloc(sizeof(int) * (nb));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < nb)
		res[i] = 1;
	return (res);
}

pthread_t	*create_threads(int nb)
{
	pthread_t	*res;

	res = malloc(sizeof(pthread_t) * (nb + 1));
	if (!res)
		return (NULL);
	res[nb] = NULL;
	return (res);
}

int	parsing(t_data *data, char **av)
{
	data->nb_philos = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	data->nb_eat = 0;
	if (data->nb_philos < 1 || data->t_to_die < 1 || \
		data->t_to_eat < 1 || data->t_to_sleep < 1)
		return (printf("Error: Invalid argument.\n"));
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat < 1)
			return (printf("Error: Invalid argument.\n"));
	}
	data->threads = create_threads(data->nb_philos);
	if (!data->threads)
		return (printf("Error: Malloc issue.\n"));
	data->forks = create_forks(data->nb_philos);
	if (!data->forks)
		return (printf("Error: Malloc issue.\n"));
	data->philos = create_philos(data->nb_philos, data->forks);
	if (!data->philos)
		return (printf("Error: Malloc issue.\n"));
	return (0);
}