/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 16:07:26 by megardes         ###   ########.fr       */
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

typedef struct s_tim
{
	unsigned int	eat;
	unsigned int	sleep;
	unsigned int	life;
	unsigned int	think;
	unsigned int	m_e;
}	t_tim;

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
	int				num;
	int				number_of_philos;
	unsigned int	first;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_thread		philo;
	int				*alive;
	t_tim			tim;
	t_fork			*forks;
	unsigned int	l_m;
	unsigned int	meals;
	unsigned int	*all_meals;
	unsigned int	*all_here;
	unsigned int	*start_god;
	unsigned int	start;
	unsigned int	death;
	t_tm			time;
}	t_thinker;

typedef struct s_philo
{
	int				number_of_mutex;
	int				number_of_philos;
	int				infos[5];
	t_thinker		*brains;
	t_thread		omnipotent;
	t_fork			forks;
	t_tim			tim;
	int				living;
	bool			print_mutex;
	bool			alive_mutex;
	bool			done_mutex;
	unsigned int	all_meals;
	unsigned int	all_here;
	unsigned int	start;
	int				*philo_rout;
	void			*(*route[3])(void *);
}	t_philo;

void			*my_think(void *in);
void			*my_eat(void *in);
void			*my_sleep(void *in);
void			free_all(t_philo *philo);
int				ml(t_mutex *in);
int				mu(t_mutex *in);
void			ft_put_str(char *str, int fd);
void			ft_put_endl(char *str, int fd);
int				not_atoi(char *num);
void			ft_putnbr(int i, int fd);
int				ft_isdigit(char *in);
int				check_in(int argc, char **argv, t_philo *philo);
unsigned int	my_time3(void);
void			god_print(t_philo *philo, unsigned int time, int num,
					char *action);
int				thinker_print(t_thinker *philo, unsigned int time, int num,
					const char *action);
int				my_usleep(t_thinker *philo, unsigned int time,
					unsigned int life, unsigned int l_m);
void			start(t_thinker *philo);
int				check_meals(t_thinker *philo);
void			*spaghetti_needs_two(t_thinker *philo);
void			*my_eat(void *in);
void			*my_sleep(void *in);
void			*my_think(void *in);
void			set_recur(int y, int *philo, int len, bool *in);
int				set_routine(t_philo *philo);
int				set_brains(t_philo *philo, int i);
int				create_mutex(t_philo *philo);
void			god_first(t_philo *philo);
void			*god_work(void *in);
int				create_thread(t_philo *philo);
void			*god_helper(t_philo *philo);

#endif