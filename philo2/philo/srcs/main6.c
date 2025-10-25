/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:53:07 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 16:06:46 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	set_routine(t_philo *philo)
{
	int	i;

	i = -1;
	philo->philo_rout = (int *)not_calloc(philo->infos[0], sizeof(int));
	if (!philo->philo_rout)
		return (0);
	while (++i < philo->infos[0])
		philo->philo_rout[i] = i % 2;
	i = 0;
	set_recur(0, philo->philo_rout, philo->infos[0], (bool *)(&i));
	philo->route[0] = my_eat;
	philo->route[1] = my_think;
	philo->route[2] = my_sleep;
	return (i);
}

int	set_brains(t_philo *philo, int i)
{
	philo->number_of_mutex = i;
	if (pthread_mutex_init(&philo->forks.mutex[i], NULL))
		return (free_all(philo), 0);
	philo->brains[i].number_of_philos = philo->infos[0];
	philo->brains[i].alive = &philo->living;
	philo->brains[i].forks = &philo->forks;
	philo->brains[i].num = i;
	philo->brains[i].tim = philo->tim;
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
	philo->print_mutex = pthread_mutex_init(&philo->forks.print, NULL);
	philo->alive_mutex = pthread_mutex_init(&philo->forks.live, NULL);
	philo->done_mutex = pthread_mutex_init(&philo->forks.done, NULL);
	pthread_mutex_init(&philo->forks.start, NULL);
	pthread_mutex_init(&philo->forks.here, NULL);
	if (philo->print_mutex || philo->alive_mutex || philo->done_mutex)
		return (free_all(philo), 0);
	while (++i < philo->infos[0])
		if (!set_brains(philo, i))
			return (0);
	return (1);
}

void	god_first(t_philo *philo)
{
	while (true)
	{
		ml(&philo->forks.here);
		if (philo->all_here == (unsigned int)philo->infos[0])
		{
			ml(&philo->forks.start);
			philo->start = 1;
			mu(&philo->forks.start);
			mu(&philo->forks.here);
			break ;
		}
		mu(&philo->forks.here);
		usleep(1);
	}
}

void	*god_work(void *in)
{
	t_philo				*philo;

	philo = (t_philo *)in;
	god_first(philo);
	while (true)
	{
		if (philo->infos[4] != -1)
		{
			ml(&philo->forks.done);
			if (philo->all_meals == philo->infos[0] * philo->tim.m_e)
				return (mu(&philo->forks.done), NULL);
			mu(&philo->forks.done);
		}
		ml(&philo->forks.live);
		if (philo->living != -1)
			return (god_helper(philo));
		mu(&philo->forks.live);
		usleep(1);
	}
}
