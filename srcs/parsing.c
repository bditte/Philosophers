/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:01:52 by bditte            #+#    #+#             */
/*   Updated: 2021/09/22 12:00:11 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**create_philos(int nb_philos, t_data *data)
{
	t_philo **res;
	int		i;

	res = malloc(sizeof(*res) * (nb_philos + 1));
	if (!res)
		return (NULL);
	res[nb_philos] = NULL;
	i = -1;
	while (++i < nb_philos)
	{
		res[i] = malloc(sizeof(t_philo));
		if (!res[i])
			return (NULL);
		res[i]->i = i;
		res[i]->last_eat = 0;
		res[i]->state = -1;
		res[i]->ttdie = data->ttdie;
		res[i]->tteat = data->tteat;
		res[i]->ttsleep = data->ttsleep;
		res[i]->nb_philos = data->nb_philos;
		res[i]->nb_eat = data->nb_eat;
	}
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
	data->ttdie = ft_atoi(av[2]);
	data->tteat = ft_atoi(av[3]);
	data->ttsleep = ft_atoi(av[4]);
	data->nb_eat = 0;
	if (data->nb_philos < 1 || data->ttdie < 1 || \
		data->tteat < 1 || data->ttsleep < 1)
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
	data->philos = create_philos(data->nb_philos, data);
	if (!data->philos)
		return (printf("Error: Malloc issue.\n"));
	return (0);
}