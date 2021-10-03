/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 09:43:14 by bditte            #+#    #+#             */
/*   Updated: 2021/10/03 18:01:01 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	write(STDOUT_FILENO, s, i);
	return (0);
}

void	ft_putnbr(int n)
{
	char	c;

	if (n < 0)
	{
		write(STDOUT_FILENO, "-", 1);
		if (n == -2147483648)
		{
			write(STDOUT_FILENO, "2", 1);
			n = -147483648;
		}
		n *= -1;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(STDOUT_FILENO, &c, 1);
}

const char	*get_message(int type)
{
	if (type == EATING)
		return ("is eating");
	if (type == DEAD)
		return ("died");
	if (type == SLEEPING)
		return ("is sleeping");
	if (type == THINKING)
		return ("is thinking");
	return ("has taken a fork");
}

int	display_action(int i, int type, pthread_mutex_t *lock)
{
	static int	displayed;

	if (type == INIT)
	{
		displayed = 0;
		return (0);
	}
	pthread_mutex_lock(lock);
	if (!displayed)
	{
		if (type == DEAD)
			displayed = 1;
		ft_putnbr(get_curr_time(0));
		write(STDOUT_FILENO, " ", 1);
		ft_putnbr(i + 1);
		write(STDOUT_FILENO, " ", 1);
		ft_putstr(get_message(type));
		write(STDOUT_FILENO, "\n", 1);
	}
	pthread_mutex_unlock(lock);
	return (0);
}
