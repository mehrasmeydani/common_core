/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/07/26 13:37:56 by megardes         ###   ########.fr       */
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
	ssize_t			infos[5];
	bool			alive;
	ssize_t			*philo_rout;
	pthread_t		*philos;
	pthread_mutex_t	*mutex;
	void			*(*route_0)(void *);
	void			*(*route_1)(void *);
	void			*(*route_2)(void *);
}	t_philo;

#endif