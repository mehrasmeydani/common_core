/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:59:45 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 02:07:39 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	put_fork(t_thinker *philo)
{
	if (philo->last_philo)
	{
		mu(philo->right_fork);
		mu(philo->left_fork);
	}
	else
	{
		mu(philo->left_fork);
		mu(philo->right_fork);
	}
}

int	take_fork(t_thinker *philo)
{
	if (philo->last_philo)
	{
		ml(philo->left_fork);
		if (thinker_print(philo, philo->first,
				philo->num, "has taken a fork"))
			return (mu(philo->left_fork), 0);
		ml(philo->right_fork);
		if (thinker_print(philo, philo->first,
				philo->num, "has taken a fork"))
			return (mu(philo->right_fork), mu(philo->left_fork), 0);
		return (1);
	}
	ml(philo->right_fork);
	if (thinker_print(philo, philo->first,
			philo->num, "has taken a fork"))
		return (mu(philo->right_fork), 0);
	ml(philo->left_fork);
	if (thinker_print(philo, philo->first,
			philo->num, "has taken a fork"))
		return (mu(philo->left_fork), mu(philo->right_fork), 0);
	return (1);
}
