/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/07/31 23:03:08 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _XOPEN_SOURCE 500

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "mylib.h"


typedef pthread_t		t_thread;
typedef	pthread_mutex_t	t_mutex;

typedef struct s_times
{
	int	eat;
	int	think;
	int	sleep;
	int	life;
}	t_times;

typedef struct s_fork
{
	t_mutex	*mutex;
	t_mutex	print;
	t_mutex	live;
}	t_fork;

typedef	struct s_thinker
{
	int			num;
	int			first;
	t_mutex		right_fork;
	t_mutex		left_fork;
	t_thread	philo;
	bool		*alive;
	t_times		*times;
	t_fork		*forks;
	int			last_meal;
	int			birth_time;
	int			meals;
}	t_thinker;

typedef struct s_philo
{
	int			number_of_mutex;
	int			number_of_philos;
	int			infos[5];
	t_thinker	*brains;
	t_thinker	omnipotent;
	t_fork		forks;
	t_times		times;
	bool		live;
	bool		print;
	bool		alive;
	int			*philo_rout;
	void		*(*route[3])(void *);
}	t_philo;

void	*my_think(void *in);
void	*my_eat(void *in);
void	*my_sleep(void *in);

#endif