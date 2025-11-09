/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 12:25:34 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 12:27:44 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*spaghetti_needs_two(t_thinker *philo)
{
	ml(philo->left_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->left_fork), NULL);
	if (my_usleep(philo, philo->times.life,
			philo->times.life, philo->last_meal))
		return (mu(philo->left_fork), NULL);
	return (NULL);
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
		if (i % 100 == 0)
		{
			if (philo->infos[4] != -1 && god_mealcheck(philo))
				return (NULL);
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
		usleep(50);
	}
}
