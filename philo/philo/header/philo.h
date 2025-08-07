/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/08/07 17:44:35 by megardes         ###   ########.fr       */
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
# include <sys/time.h>
# include <sys/types.h>
# include "mylib.h"


typedef pthread_t		t_thread;
typedef	pthread_mutex_t	t_mutex;
typedef	struct timeval	t_tm;

typedef struct s_times
{
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	life;
	unsigned int	think;
	unsigned int	must_eat;
}	t_times;

typedef struct s_fork
{
	t_mutex	*mutex;
	t_mutex	print;
	t_mutex	live;
	t_mutex	done;
}	t_fork;

typedef	struct s_thinker
{
	int				num;
	unsigned int	first;
	t_mutex			right_fork;
	t_mutex			left_fork;
	t_thread		philo;
	int				*alive;
	t_times			times;
	t_fork			*forks;
	unsigned int	last_meal;
	unsigned int	meals;
	unsigned int	current_time;
	t_tm			time;
}	t_thinker;

typedef struct s_philo
{
	int			number_of_mutex;
	int			number_of_philos;
	int			infos[5];
	t_thinker	*brains;
	t_thread	omnipotent;
	t_fork		forks;
	t_times		times;
	int			living;
	bool		print_mutex;
	bool		alive_mutex;
	bool		done_mutex;
	int			*philo_rout;
	void		*(*route[3])(void *);
}	t_philo;

void	*my_think(void *in);
void	*my_eat(void *in);
void	*my_sleep(void *in);

#endif