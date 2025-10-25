/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:43:26 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 16:00:02 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	not_atoi(char *num)
{
	int	i;
	int	out;

	i = -1;
	out = 0;
	while (num[++i])
		out = out * 10 + num[i] - '0';
	return (out);
}

void	ft_putnbr(int i, int fd)
{
	if (i != 0)
		return (ft_putnbr(i / 10, fd),
			(void)write(fd, &"0123456789"[i % 10], 1));
}

int	ft_isdigit(char *in)
{
	int	i;

	i = -1;
	while (in[++i])
		if (!(in[i] >= '0' && in[i] <= '9'))
			return (0);
	return (1);
}

int	check_in(int argc, char **argv, t_philo *philo)
{
	unsigned int	i;

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
	philo->tim.life = philo->infos[1] * 10;
	philo->tim.eat = philo->infos[2] * 10;
	philo->tim.sleep = philo->infos[3] * 10;
	i = (philo->infos[1] - philo->infos[2] - philo->infos[3]) * 10;
	philo->tim.think = i;
	if (philo->infos[4] != -1)
		philo->tim.m_e = philo->infos[4];
	return (1);
}

unsigned int	my_time3(void)
{
	t_tm	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((unsigned int)time.tv_usec / 100 + (time.tv_sec % 100000 * 10000));
}
