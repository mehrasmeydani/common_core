/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 15:41:29 by megardes         ###   ########.fr       */
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
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_tm;
typedef unsigned int	t_ui;

typedef struct s_times
{
	t_ui	eat;
	t_ui	sleep;
	t_ui	life;
	t_ui	think;
	t_ui	must_eat;
}	t_times;

typedef struct s_fork
{
	t_mutex	*mutex;
	t_mutex	print;
	t_mutex	live;
	t_mutex	done;
	t_mutex	here;
	t_mutex	start;
}	t_fork;

typedef struct s_thinker
{
	int			num;
	t_ui		number_of_philos;
	t_ui		first;
	t_mutex		*right_fork;
	t_mutex		*left_fork;
	t_thread	philo;
	int			*alive;
	t_times		times;
	t_fork		*forks;
	t_ui		last_meal;
	t_ui		meals;
	t_ui		*all_meals;
	t_ui		*all_here;
	t_ui		*start_god;
	t_ui		start;
	t_ui		death;
	void		*(*f)(struct s_thinker *);
	t_tm		time;
	bool		last_philo;
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
	t_ui		all_meals;
	t_ui		all_here;
	t_ui		start;
	int			*philo_rout;
	void		*(*route[3])(t_thinker *);
}	t_philo;

void	*my_think(t_thinker *in);
void	*my_eat(t_thinker *in);
void	*my_sleep(t_thinker *in);
void	free_all(t_philo *philo);
int		ml(t_mutex *in);
int		mu(t_mutex *in);
int		check_in(int argc, char **argv, t_philo *philo);
int		thinker_print(t_thinker *philo, t_ui time, int num,
			const char *action);
t_ui	my_time(void);
int		my_usleep(t_thinker *philo, t_ui time,
			t_ui life, t_ui last_meal);
void	god_start(t_philo *philo);
void	*start(void *in);
int		check_meals(t_thinker *philo);
int		take_fork(t_thinker *philo);
void	put_fork(t_thinker *philo);
void	*spaghetti_needs_two(t_thinker *in);
int		set_routine(t_philo *philo);
void	*god_work(void *in);
int		create_thread(t_philo *philo);
int		god_mealcheck(t_philo *philo);
void	free_threads(t_philo *philo, int i);

#endif