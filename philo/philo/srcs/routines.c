/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 22:00:40 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 02:20:12 by megardes         ###   ########.fr       */
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

void	*my_eat(t_thinker *philo)
{
	if (!take_fork(philo))
		return (NULL);
	philo->last_meal = my_time();
	if (thinker_print(philo, philo->first, philo->num, "is eating"))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	if (my_usleep(philo, philo->times.eat, philo->times.life, philo->last_meal))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	put_fork(philo);
	if (philo->times.must_eat != 0 && check_meals(philo))
		return (NULL);
	return (my_sleep(philo));
}

void	*my_sleep(t_thinker *philo)
{
	if (thinker_print(philo, philo->first, philo->num, "is sleeping"))
		return (NULL);
	if (my_usleep(philo, philo->times.sleep, philo->times.life,
			philo->last_meal))
		return (NULL);
	return (my_think(philo));
}

void	*my_think(t_thinker *philo)
{
	if (thinker_print(philo, philo->first, philo->num, "is thinking"))
		return (NULL);
	if (my_usleep(philo, philo->times.think, philo->times.life,
			philo->last_meal))
		return (NULL);
	return (my_eat(philo));
}

void	set_recur(int y, int *philo, int len, bool *in)
{
	int	x;

	x = -1;
	if (y == len)
		return ((void)(*in = 1));
	else
	{
		while (++x < 3)
		{
			if (*in == 0 && (y == 0 || (y != len - 1 && philo[y - 1] != x)
					|| (y == len - 1 && philo[y - 1] != x && philo[0] != x)))
			{
				if (!((y != 0 && y != len - 1 && philo[y - 1] != philo[y])
						|| (y == len - 1 && philo[y - 1] != philo[y]
							&& philo[0] != philo[y])))
					philo[y] = x;
				set_recur(y + 1, philo, len, in);
			}
		}
	}
}

int	set_routine(t_philo *philo)
{
	int	i;

	i = -1;
	philo->philo_rout = (int *)not_calloc(philo->infos[0], sizeof(int));
	if (!philo->philo_rout)
		return (0);
	while (++i < philo->infos[0])
		philo->philo_rout[i] = i % 2;
	if (philo->infos[0] % 2)
		philo->philo_rout[i - 1] += 1;
	else
	{
		i = 0;
		set_recur(0, philo->philo_rout, philo->infos[0], (bool *)(&i));
	}
	philo->route[0] = my_eat;
	philo->route[1] = my_think;
	philo->route[2] = my_sleep;
	return (1);
}
