/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:05:33 by bditte            #+#    #+#             */
/*   Updated: 2021/09/30 10:40:38 by bditte           ###   ########.fr       */
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
	free(data->all_alive);
	free(data->all_ate);
	free(data->ate_lock);
	free(data->alive_lock);
	free(data->threads);
	free(data->forks);
	return (0);
}
