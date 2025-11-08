/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:27:53 by megardes          #+#    #+#             */
/*   Updated: 2025/11/08 21:28:26 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	free_all(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->philo_rout)
		free(philo->philo_rout);
	if (philo->forks.mutex)
	{
		while (++i < philo->infos[0])
			pthread_mutex_destroy(&philo->forks.mutex[i]);
		free(philo->forks.mutex);
		if (philo->alive_mutex)
			pthread_mutex_destroy(&philo->forks.live);
		if (philo->print_mutex)
			pthread_mutex_destroy(&philo->forks.print);
		if (philo->done_mutex)
			pthread_mutex_destroy(&philo->forks.done);
	}
}
