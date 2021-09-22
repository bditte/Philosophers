/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:05:33 by bditte            #+#    #+#             */
/*   Updated: 2021/09/22 11:40:51 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_philos(t_philo **philos, int nb_philos)
{
	int	i;

	i = 0;
	while (i < nb_philos)
		free(philos[i++]);
	free(philos);
	return (0);
}

int	free_everything(t_data *data)
{
	int	i;

	free_philos(data->philos, data->nb_philos);
	free(data->threads);
	i = -1;
	return (0);
}