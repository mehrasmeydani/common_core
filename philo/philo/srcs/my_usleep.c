/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:46:06 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 02:48:25 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	my_usleep(t_thinker *philo, t_ui time, t_ui life,
	t_ui last_meal)
{
	t_ui	current_time;
	t_ui	pass_time;

	current_time = my_time();
	pass_time = my_time();
	while (current_time - pass_time < time || life == time)
	{
		if ((current_time - last_meal) / 5 > (life) / 5)
		{
			ml(&philo->forks->live);
			if (*philo->alive != -1)
				return (mu(&philo->forks->live), 1);
			*philo->alive = philo->num;
			mu(&philo->forks->live);
			return (1);
		}
		current_time = my_time();
		usleep(25);
	}
	usleep(10);
	return (0);
}
