/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:29:56 by bditte            #+#    #+#             */
/*   Updated: 2021/10/02 10:49:13 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (ft_print_error("Error: Wrong number of arguments\n"));
	if (parsing(&data, av))
		return (1);
	if (manage_philos(&data))
		return (1);
	free_everything(&data);
	return (0);
}
