/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/07/26 15:37:59 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

typedef struct s_philo
{
	t_thinker		*brains;
	ssize_t			infos[5];
	bool			alive;
	ssize_t			*philo_rout;
	pthread_mutex_t	*mutex;
	void			*(*route_0)(void *);
	void			*(*route_1)(void *);
	void			*(*route_2)(void *);
}	t_philo;

typedef	struct s_phil
{
	ssize_t		eat;
	ssize_t		think;
	ssize_t		sleep;
	ssize_t		life;
	pthread_t	philo;
	ssize_t		num;
}	t_thinker;


#endif