/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:30:15 by bditte            #+#    #+#             */
/*   Updated: 2021/09/21 14:59:43 by bditte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define EATING 0
# define SLEEPING 1
# define THINKING 2

typedef	struct	s_philo
{
	int			i;
	int			state;
	int			last_eat;
	int			sleep_start;
	int			*forks;
	pthread_mutex_t	mutex_fork;
}				t_philo;

typedef struct	s_data
{
	int			nb_philos;
	int			t_to_die;
	int			t_to_eat;
	int			t_to_sleep;
	int			nb_eat;
	int			starting_time;
	int			*forks;
	t_philo		**philos;
	pthread_t	*threads;
}				t_data;

int	parsing(t_data *data, char **av);
int	manage_philos(t_data *data);

/*
** UTILS
*/

int	ft_atoi(const char *str);
int	ft_isdigit(char c);
int	free_philos(t_philo **philos, int nb_philos);
int	get_time_in_ms();
int	free_everything(t_data *data);
#endif