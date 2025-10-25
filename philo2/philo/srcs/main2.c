/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:42:10 by megardes          #+#    #+#             */
/*   Updated: 2025/10/25 15:43:00 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	free_all(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->philo_rout)
		free(philo->philo_rout);
	if (philo->forks.mutex)
	{
		while (++i < philo->infos[0])
			pthread_mutex_destroy(&philo->forks.mutex[i]);
		free(philo->forks.mutex);
		if (philo->alive_mutex)
			pthread_mutex_destroy(&philo->forks.live);
		if (philo->print_mutex)
			pthread_mutex_destroy(&philo->forks.print);
		if (philo->done_mutex)
			pthread_mutex_destroy(&philo->forks.done);
	}
}

int	ml(t_mutex *in)
{
	return (pthread_mutex_lock(in));
}

int	mu(t_mutex *in)
{
	return (pthread_mutex_unlock(in));
}

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
