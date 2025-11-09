/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 16:12:00 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	set_brains(t_philo *philo, int i)
{
	philo->number_of_mutex = i;
	if (pthread_mutex_init(&philo->forks.mutex[i], NULL))
		return (free_all(philo), 0);
	philo->brains[i].number_of_philos = philo->infos[0];
	philo->brains[i].alive = &philo->living;
	philo->brains[i].forks = &philo->forks;
	philo->brains[i].num = i;
	philo->brains[i].times = philo->times;
	philo->brains[i].all_meals = &philo->all_meals;
	philo->brains[i].all_here = &philo->all_here;
	philo->brains[i].start_god = &philo->start;
	philo->brains[i].right_fork = &philo->forks.mutex[i];
	if (i == 0)
		philo->brains[i].left_fork = &philo->forks.mutex[philo->infos[0] - 1];
	else
		philo->brains[i].left_fork = &philo->forks.mutex[i - 1];
	return (1);
}

int	create_mutex(t_philo *philo)
{
	int	i;

	philo->brains = (t_thinker *)calloc(philo->infos[0], sizeof(t_thinker));
	philo->forks.mutex = (t_mutex *)calloc(philo->infos[0], sizeof(t_mutex));
	if (!philo->brains || !philo->forks.mutex)
		return (free_all(philo), 0);
	i = -1;
	philo->living = -1;
	while (++i < philo->infos[0])
		if (!set_brains(philo, i))
			return (0);
	philo->print_mutex = pthread_mutex_init(&philo->forks.print, NULL);
	philo->alive_mutex = pthread_mutex_init(&philo->forks.live, NULL);
	philo->done_mutex = pthread_mutex_init(&philo->forks.done, NULL);
	pthread_mutex_init(&philo->forks.start, NULL);
	pthread_mutex_init(&philo->forks.here, NULL);
	if (philo->print_mutex || philo->alive_mutex || philo->done_mutex)
		return (free_all(philo), 0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(philo));
	if (!check_in(argc, argv, &philo))
		return (1);
	if (!set_routine(&philo))
		return (1);
	if (!create_mutex(&philo))
		return (1);
	if (!create_thread(&philo))
		return (1);
	free_all(&philo);
	return (0);
}
