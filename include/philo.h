/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bditte <bditte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:30:15 by bditte            #+#    #+#             */
/*   Updated: 2021/09/24 16:37:33 by bditte           ###   ########.fr       */
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
# define DONE_EATING 3
# define DEAD 8000

typedef	struct	s_philo
{
	int			i;
	int			did_eat;
	int			state;
	int			last_eat;
	int			sleep_start;
	int			nb_philos;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			nb_eat;
	int			starting_time;
	int			*all_alive;
	pthread_mutex_t	*lock;
}				t_philo;

typedef struct	s_data
{
	int			nb_philos;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			nb_eat;
	int			starting_time;
	int			*all_alive;
	t_philo		**philos;
	pthread_mutex_t	mutex;
	pthread_t	*threads;
}				t_data;

int		parsing(t_data *data, char **av);
int		manage_philos(t_data *data);
void	*philosopher(void *data);
int		init_threads(t_data *data);

/*
** UTILS
*/

int	ft_atoi(const char *str);
int	ft_isdigit(char c);
int	get_time_in_ms();
int	is_dead(t_philo *philo);
int	ft_sleep(t_philo *philo, int time);
int	free_everything(t_data *data);
int	free_philos(t_philo **philos, int nb_philos);
#endif