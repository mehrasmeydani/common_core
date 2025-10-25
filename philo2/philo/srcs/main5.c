/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:48:33 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 16:01:05 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*spaghetti_needs_two(t_thinker *philo)
{
	ml(philo->left_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->left_fork), NULL);
	if (my_usleep(philo, philo->tim.life, philo->tim.life, philo->l_m))
		return (mu(philo->left_fork), NULL);
	return (NULL);
}

void	*my_eat(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->start)
		start(philo);
	if (philo->number_of_philos == 1)
		return (spaghetti_needs_two(philo));
	ml(philo->left_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->left_fork), NULL);
	ml(philo->right_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	if (thinker_print(philo, philo->first, philo->num, "is eating"))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	philo->l_m = my_time3();
	if (my_usleep(philo, philo->tim.eat, philo->tim.life, philo->l_m))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	mu(philo->right_fork);
	mu(philo->left_fork);
	if (philo->tim.m_e != 0 && check_meals(philo))
		return (NULL);
	my_sleep(in);
	return (NULL);
}

void	*my_sleep(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->start)
		start(philo);
	if (thinker_print(philo, philo->first, philo->num, "is sleeping"))
		return (NULL);
	if (my_usleep(philo, philo->tim.sleep, philo->tim.life,
			philo->l_m))
		return (NULL);
	if (philo->tim.m_e != 0)
	{
		ml(&philo->forks->done);
		if (*philo->all_meals == philo->number_of_philos * philo->tim.m_e)
			return (mu(&philo->forks->done), NULL);
		mu(&philo->forks->done);
	}
	my_think(in);
	return (NULL);
}

void	*my_think(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->start)
		start(philo);
	if (thinker_print(philo, philo->first, philo->num, "is thinking"))
		return (NULL);
	if (my_usleep(philo, philo->tim.think / 2, philo->tim.life,
			philo->l_m))
		return (NULL);
	if (philo->tim.m_e != 0)
	{
		ml(&philo->forks->done);
		if (*philo->all_meals == philo->number_of_philos * philo->tim.m_e)
			return (mu(&philo->forks->done), NULL);
		mu(&philo->forks->done);
	}
	my_eat(in);
	return (NULL);
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
