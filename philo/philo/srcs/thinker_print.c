/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinker_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:37:58 by megardes          #+#    #+#             */
/*   Updated: 2025/11/08 21:38:59 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	thinker_print(t_thinker *philo, unsigned int time, int num,
	const char *action)
{
	ml(&philo->forks->live);
	if (my_time() - philo->last_meal > philo->times.life + 2)
		return (*philo->alive = philo->num, mu(&philo->forks->live), 1);
	ml(&philo->forks->print);
	if (*philo->alive != -1)
		return (mu(&philo->forks->live), mu(&philo->forks->print), 1);
	printf("%u %d %s\n", (my_time() - time) / 10, num, action);
	mu(&philo->forks->print);
	mu(&philo->forks->live);
	return (0);
}
