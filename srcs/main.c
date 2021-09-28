/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:29:56 by bditte            #+#    #+#             */
/*   Updated: 2021/09/28 14:33:55 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf("Error: Wrong number of arguments\n"));
	if (parsing(&data, av))
		return (1);
	if (manage_philos(&data))
		return (1);
	free_everything(&data);
	//system("leaks philo");
	return (0);
}
