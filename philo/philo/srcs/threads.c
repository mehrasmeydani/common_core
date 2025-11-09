/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:24:28 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 12:24:53 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	create_and_set_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->infos[0])
	{
		philo->number_of_philos = i;
		philo->brains[i].first = my_time();
		philo->brains[i].last_meal = philo->brains[i].first;
		if (philo->infos[0] == 1)
			philo->brains[i].f = &spaghetti_needs_two;
		else
			philo->brains[i].f = philo->route[philo->philo_rout[i]];
		if (i == philo->infos[0] - 1)
			philo->brains[i].last_philo = 1;
		if (pthread_create(&philo->brains[i].philo, NULL,
				start, &philo->brains[i]))
			return (free_threads(philo, i), -1);
	}
	return (i);
}

int	create_thread(t_philo *philo)
{
	int	i;
	int	j;

	if (pthread_create(&philo->omnipotent, NULL, god_work, philo))
		return (free_all(philo), 0);
	i = create_and_set_threads(philo);
	if (i == -1)
		return (0);
	pthread_join(philo->omnipotent, NULL);
	j = -1;
	while (++j < i)
		pthread_join(philo->brains[j].philo, NULL);
	free(philo->brains);
	return (1);
}
