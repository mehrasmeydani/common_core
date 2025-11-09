/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:52:36 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 01:39:37 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*start(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	philo->start = 1;
	ml(&philo->forks->here);
	*philo->all_here = *philo->all_here + 1;
	mu(&philo->forks->here);
	while (true)
	{
		ml(&philo->forks->start);
		if (*philo->start_god)
		{
			mu(&philo->forks->start);
			philo->first = my_time();
			if (philo->number_of_philos % 2 == 0 && philo->num % 2 == 1
				&& philo->times.eat == philo->times.sleep)
				usleep(philo->times.eat / 2 * 100);
			philo->last_meal = my_time();
			break ;
		}
		mu(&philo->forks->start);
		usleep(1);
	}
	return (philo->f(philo));
}

void	god_start(t_philo *philo)
{
	while (true)
	{
		ml(&philo->forks.here);
		if (philo->all_here == (t_ui)philo->infos[0])
		{
			ml(&philo->forks.start);
			philo->start = my_time();
			mu(&philo->forks.start);
			mu(&philo->forks.here);
			break ;
		}
		mu(&philo->forks.here);
		usleep(1);
	}
}
