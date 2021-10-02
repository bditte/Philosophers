/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:01:52 by bditte            #+#    #+#             */
/*   Updated: 2021/10/02 18:09:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_vars(t_philo *philo, int i, int nb_philos)
{
	philo->i = i;
	philo->did_eat = 0;
	philo->last_eat = 0;
	philo->state = -1;
	philo->fork_left = i;
	if (i == nb_philos - 1)
		philo->fork_right = 0;
	else
		philo->fork_right = i + 1;
}

t_philo	**create_philos(int nb_philos, t_data *data)
{
	t_philo	**res;
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
		init_philo_vars(res[i], i, nb_philos);
		res[i]->nb_eat = data->nb_eat;
		res[i]->data = data;
	}
	return (res);
}

pthread_t	*create_threads(int nb)
{
	pthread_t	*res;
//	int			i;

	res = malloc(sizeof(pthread_t) * (nb + 1));
	if (!res)
		return (NULL);
	/*i = -1;
	while (++i < nb)
	{
		res[i] = -1;
	}*/
	res[nb] = 0;
	return (res);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (-1);
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	return (0);
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
		return (ft_print_error("Error: Invalid argument.\n"));
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat < 1)
			return (ft_print_error("Error: Invalid argument.\n"));
	}
	if (init_forks(data))
		return (ft_print_error("Error: Malloc issue.\n"));
	data->threads = create_threads(data->nb_philos);
	if (!data->threads)
	{
		free(data->forks);
		return (ft_print_error("Error: Malloc issue.\n"));
	}
	data->philos = create_philos(data->nb_philos, data);
	if (!data->philos)
	{
		free(data->forks);
		free(data->threads);
		return (ft_print_error("Error: Malloc issue.\n"));
	}
	return (0);
}
