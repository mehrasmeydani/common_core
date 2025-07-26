/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/07/26 15:18:14 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_put_str(char *str, int fd)
{
	while (*str)
		write (fd, str++, 1);
}

void	ft_put_endl(char *str, int fd)
{
	while (*str)
		write (fd, str++, 1);
	write(fd, "\n", 1);
}

ssize_t	atos(char *num)
{
	ssize_t	i;
	ssize_t	out;

	i = -1;
	out = 0;
	while (num[++i])
		out += out * 10 + num[i] - '0';
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
	ssize_t	i;

	i = -1;
	while (in[++i])
		if (!(in[i] >= '0' && in[i] <= '9'))
			return (0);
	return (1);
}

int	check_in(int argc, char **argv, t_philo *philo)
{
	philo->infos[4] = -1;
	if (argc < 5)
		return (ft_put_endl("Not enough arguments", 2), 0);
	while (--argc > 0)
	{
		if ((argv[argc][0] != '+' || argv[argc]++) && !ft_isdigit(argv[argc]))
			return (ft_put_str("Argument ", 2), ft_putnbr(argc, 2),
				ft_put_endl(": is not a valid number", 2), 0);
		else
			philo->infos[argc - 1] = atos(argv[argc]);
	}
	return (1);
}

void	set_recur(ssize_t y, ssize_t *philo, ssize_t len, bool *in)
{
	ssize_t	x;

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
				if (!((y != len - 1 && philo[y - 1] != philo[y])
				|| (y == len - 1 && philo[y - 1] != philo[y] && philo[0] != philo[y])))
					philo[y] = x;
				set_recur(y + 1, philo, len, in);
			}
		}	
	}
		
}

int	set_routine(t_philo *philo)
{
	ssize_t	i;

	i = -1;
	philo->philo_rout = (ssize_t *)malloc(philo->infos[0] * sizeof(ssize_t));
	if (!philo->philo_rout)
		return (0);
	while (++i < philo->infos[0])
		philo->philo_rout[i] = i % 3;
	i = 0;
	set_recur(0, philo->philo_rout, philo->infos[0], (bool *)(&i));
	return (i);
}



int	create_philos(t_philo *philo)
{
	ssize_t	i;

	philo->philos = (pthread_t *)malloc(philo->infos[0] * sizeof(pthread_t));
	philo->mutex = (pthread_t *)malloc(philo->infos[0]
			* sizeof(pthread_mutex_t));
	if (!philo->philos || !philo->mutex)
		return (free_all(philo), 0);
	i = -1;
	while (++i < philo->infos[0])
		if (!pthread_mutex_init(&philo->mutex[i], NULL))
			return (free_all(philo), 0);
	i = -1;
	while (++i < philo->infos[0])
		if (!pthread_create(&philo->philo_rout[i], NULL, philo->route_0, philo))
			return (free_all(philo), 0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo.infos, 0, sizeof(philo.infos));
	if (!check_in(argc, argv, &philo))
		return (1);
	if (!set_routine(&philo))
		return (1);
	if (!create_philos(&philo))
		return (free_all(&philo), 1);
}