/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/07/08 21:29:40 by megardes         ###   ########.fr       */
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
	ssize_t out;

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
	ssize_t i;

	i = -1;
	while (in[++i])
		if (!(in[i] >= '0' && in[i] <= '9'))
			return (0);
	return (1);
}

int	check_in(int argc, char **argv, t_philo *philo)
{
	if (argc < 5)
		return (ft_put_endl("Not enough arguments", 2), 0);	
	while (--argc > 0)
		if ((argv[argc][0] != '+' || argv[argc]++) && !ft_isdigit(argv[argc]))
			return (ft_put_str("Argument ", 2), ft_putnbr(argc, 2),
				ft_put_endl(": is not a valid number", 2), 0);
		else
			philo->info_philos[argc - 1] = atos(argv[argc]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo.info_philos, -1, sizeof(philo.info_philos));
	if (!check_in(argc, argv, &philo))
		return (0);
}