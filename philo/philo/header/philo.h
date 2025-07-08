/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:22:46 by megardes          #+#    #+#             */
/*   Updated: 2025/07/08 21:26:50 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <bits/pthreadtypes.h>
# include <unistd.h>
# include <string.h>

typedef struct s_philo
{
	ssize_t			info_philos[5];
	ssize_t			*philo_sits;
	pthread_t		*philos;
	pthread_mutex_t	*mutex;
	void			*(*route_1)(void *);
	void			*(*route_2)(void *);
	void			*(*route_3)(void *);
}	t_philo;

#endif