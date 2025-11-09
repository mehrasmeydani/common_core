/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 02:48:56 by megardes         ###   ########.fr       */
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

void	*god_work(void *in)
{
	t_philo				*philo;
	size_t				i;

	philo = (t_philo *)in;
	god_start(philo);
	i = 0;
	while (true)
	{
		if (i % 40 == 0)
		{
			if (philo->infos[4] != -1)
			{
				ml(&philo->forks.done);
				if (philo->all_meals == (t_ui)philo->infos[0])
					return (mu(&philo->forks.done), NULL);
				mu(&philo->forks.done);
			}
			ml(&philo->forks.live);
			if (philo->living != -1)
			{
				ml(&philo->forks.print);
				printf("%u %d %s\n", (my_time() - philo->start) / 10,
					philo->living, "died");
				return (mu(&philo->forks.print), mu(&philo->forks.live), NULL);
			}
			mu(&philo->forks.live);
		}
		i++;
		usleep(25);
	}
}

int	create_thread(t_philo *philo)
{
	int	i;

	i = -1;
	if (pthread_create(&philo->omnipotent, NULL, god_work, philo))
		return (free_all(philo), 0);
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
			return (free_all(philo), 0);
	}
	pthread_join(philo->omnipotent, NULL);
	i = -1;
	while (++i < philo->number_of_philos + 1)
		pthread_join(philo->brains[i].philo, NULL);
	free(philo->brains);
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
