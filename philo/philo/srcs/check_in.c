/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:31:31 by megardes          #+#    #+#             */
/*   Updated: 2025/11/09 04:22:43 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void set_invalid(t_philo *philo)
{
	const t_ui	sleep = philo->times.sleep;
	const t_ui	eat = philo->times.eat;
	const t_ui	life = philo->times.life;

	if (philo->infos[0] % 2)
	{
		if (life - eat == eat + sleep)
			philo->times.think = life;
	}
}

static void	set_think(t_philo *philo)
{
	if (philo->infos[0] % 2)
	{
		if (philo->times.eat <= philo->times.sleep)
		{
			philo->times.think = (philo->times.eat * 2 - philo->times.sleep)
				* (philo->times.eat * 2 > philo->times.sleep) / 2;
		}
		else 
			philo->times.think = (philo->times.eat - philo->times.sleep)
				* 3 / 2;
	}
	else
	{
		if (philo->times.eat > philo->times.sleep)
			philo->times.think = (philo->times.eat - philo->times.sleep);
		else
		{
			philo->times.think = (philo->times.life - philo->times.eat
					- philo->times.sleep) / 2;
			if (philo->times.think < philo->times.eat / 2)
				philo->times.think = 0;
		}
	}
}

int	check_in(int argc, char **argv, t_philo *philo)
{
	philo->infos[4] = -1;
	if (argc < 5)
		return (ft_put_endl("Not enough arguments", 2), 0);
	while (--argc > 0)
	{
		if (((argv[argc][0] != '+' || argv[argc]++) && !ft_isdigit(argv[argc]))
			|| argv[argc][0] == '0')
			return (ft_put_str("Argument ", 2), ft_putnbr(argc, 2),
				ft_put_endl(": is not a valid number", 2), 0);
		else
			philo->infos[argc - 1] = not_atoi(argv[argc]);
	}
	philo->times.life = philo->infos[1] * 10;
	philo->times.eat = philo->infos[2] * 10;
	philo->times.sleep = philo->infos[3] * 10;
	set_think(philo);
	set_invalid(philo);
	if (philo->infos[4] != -1)
		philo->times.must_eat = philo->infos[4];
	return (1);
}
