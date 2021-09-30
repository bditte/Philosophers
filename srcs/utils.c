/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:36:20 by bditte            #+#    #+#             */
/*   Updated: 2021/09/30 12:02:54 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	nbr;

	nbr = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		nbr *= 10;
		nbr += *str - '0';
		str++;
	}
	return (nbr);
}

int	ft_isdigit(char c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	get_time_in_ms(void)
{
	struct timeval	curr_time;
	int				res;

	res = 0;
	gettimeofday(&curr_time, NULL);
	res = curr_time.tv_sec * 1000;
	res += curr_time.tv_usec / 1000;
	return (res);
}

int	get_curr_time(int init)
{
	static int		start_time;

	if (init)
	{
		start_time = get_time_in_ms();
		return (0);
	}
	return (get_time_in_ms() - start_time);
}
