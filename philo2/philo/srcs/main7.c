/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:54:54 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 16:05:51 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	create_thread(t_philo *philo)
{
	int	i;

	i = -1;
	if (pthread_create(&philo->omnipotent, NULL, god_work, philo))
		return (free_all(philo), 0);
	while (++i < philo->infos[0])
	{
		philo->number_of_philos = i;
		philo->brains[i].first = my_time3();
		philo->brains[i].l_m = philo->brains[i].first;
		if (pthread_create(&philo->brains[i].philo, NULL,
				philo->route[philo->philo_rout[i]], &philo->brains[i]))
			return (free_all(philo), 0);
	}
	pthread_join(philo->omnipotent, NULL);
	i = -1;
	while (++i < philo->number_of_philos + 1)
		pthread_join(philo->brains[i].philo, NULL);
	free(philo->brains);
	return (1);
}

void	*god_helper(t_philo *philo)
{
	unsigned int		num;
	t_thinker			brain;

	num = philo->living;
	brain = philo->brains[num];
	god_print(philo, (brain.death - brain.first), num, "died");
	mu(&philo->forks.live);
	return (NULL);
}
