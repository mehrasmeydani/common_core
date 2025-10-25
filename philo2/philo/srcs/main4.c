/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:45:22 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 15:51:05 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	god_print(t_philo *philo, unsigned int time, int num, char *action)
{
	ml(&philo->forks.print);
	printf("%d %d %s\n", time / 10, num, action);
	mu(&philo->forks.print);
}

int	thinker_print(t_thinker *philo, unsigned int time, int num,
	const char *action)
{
	ml(&philo->forks->live);
	ml(&philo->forks->print);
	if (*philo->alive != -1)
		return (mu(&philo->forks->live), mu(&philo->forks->print), 1);
	else if (my_time3() - philo->l_m > philo->tim.life + 9)
		return (*philo->alive = philo->num, mu(&philo->forks->live),
			mu(&philo->forks->print), philo->death = my_time3(), 1);
	mu(&philo->forks->live);
	printf("%u %d %s\n", (my_time3() - time) / 10, num, action);
	mu(&philo->forks->print);
	return (0);
}

int	my_usleep(t_thinker *philo, unsigned int time, unsigned int life,
	unsigned int l_m)
{
	unsigned int	current_time;
	unsigned int	pass_time;

	current_time = my_time3();
	pass_time = my_time3();
	while (current_time - pass_time < time || time < 10 || time == life)
	{
		current_time = my_time3();
		if (time < 10)
		{
			usleep(philo->tim.think * 50);
			break ;
		}
		if (current_time - l_m > life + 9)
		{
			ml(&philo->forks->live);
			*philo->alive = philo->num;
			philo->death = my_time3();
			mu(&philo->forks->live);
			return (1);
		}
		usleep(200);
	}
	return (0);
}

void	start(t_thinker *philo)
{
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
			philo->first = my_time3();
			philo->l_m = my_time3();
			break ;
		}
		mu(&philo->forks->start);
		usleep(1);
	}
}

int	check_meals(t_thinker *philo)
{
	ml(&philo->forks->done);
	if (philo->meals < philo->tim.m_e)
	{
		philo->meals++;
		*(philo->all_meals) = *(philo->all_meals) + 1;
	}
	if (*philo->all_meals == philo->number_of_philos * philo->tim.m_e)
		return (mu(&philo->forks->done), 1);
	mu(&philo->forks->done);
	return (0);
}
