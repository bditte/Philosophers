/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:05:33 by bditte            #+#    #+#             */
/*   Updated: 2021/09/24 16:01:29 by bditte           ###   ########.fr       */
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
	free_philos(data->philos, data->nb_philos);
	free(data->threads);
	return (0);
}