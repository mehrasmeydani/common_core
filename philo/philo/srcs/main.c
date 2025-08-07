/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/07/31 23:06:14 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	free_all(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->philo_rout)
		free(philo->philo_rout);
	// if (philo->forks.mutex)
	// {
	// 	while (++i < philo->infos[0])
	// 		pthread_mutex_destroy(&philo->forks.mutex[i]);
	// 	free(philo->forks.mutex);
	// }
	i = -1;
	if (philo->brains)
	{
		while (++i < philo->infos[0])
			pthread_join(philo->brains[i].philo, NULL);
		free(philo->brains);
	}
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
	philo->infos[4] = -1;
	if (argc < 5)
		return (ft_put_endl("Not enough arguments", 2), 0);
	while (--argc > 0)
	{
		if ((argv[argc][0] != '+' || argv[argc]++) && !ft_isdigit(argv[argc]))
			return (ft_put_str("Argument ", 2), ft_putnbr(argc, 2),
				ft_put_endl(": is not a valid number", 2), 0);
		else
			philo->infos[argc - 1] = not_atoi(argv[argc]);
	}
	return (1);
}

void	*my_eat(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	philo->meals++;
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->forks->print);
	ft_put_endl(":left fork", 1);
	ft_put_endl(":right fork", 1);
	ft_put_endl(":eating", 1);
	pthread_mutex_unlock(&philo->forks->print);
	usleep(500);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	if (philo->meals == 5)
		return (NULL);
	my_think(in);
	return (NULL);
}

void	*my_sleep(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->first)
	{
		philo->first = 1;
		usleep(1);
	}
	pthread_mutex_lock(&philo->forks->print);
	ft_put_endl(":in sleep", 1);
	pthread_mutex_unlock(&philo->forks->print);
	usleep(500);
	my_eat(in);
	return (NULL);
}

void	*my_think(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->first)
	{
		philo->first = 1;
		usleep(1);
	}
	pthread_mutex_lock(&philo->forks->print);
	ft_put_endl(":in think", 1);
	pthread_mutex_unlock(&philo->forks->print);
	usleep(500);
	my_sleep(in);
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
				|| (y == len - 1 && philo[y - 1] != philo[y] && philo[0] != philo[y])))
					philo[y] = x;
				set_recur(y + 1, philo, len, in);
			}
		}	
	}
		
}

int	set_routine(t_philo *philo)
{
	int	i;

	i = -1;
	philo->philo_rout = (int *)not_calloc(philo->infos[0] , sizeof(int));
	if (!philo->philo_rout)
		return (0);
	while (++i < philo->infos[0])
		philo->philo_rout[i] = i % 3;
	i = 0;
	set_recur(0, philo->philo_rout, philo->infos[0], (bool *)(&i));
	philo->route[0] = my_eat;
	philo->route[1] = my_think;
	philo->route[2] = my_sleep;
	return (i);
}

int	create_mutex(t_philo *philo)
{
	int	i;

	philo->brains = (t_thinker *)calloc(philo->infos[0] , sizeof(t_thinker));
	philo->forks.mutex = (t_mutex *)calloc(philo->infos[0] , sizeof(t_mutex));
	if (!philo->brains || !philo->forks.mutex)
		return (free_all(philo), 0);
	i = -1;
	philo->print = pthread_mutex_init(&philo->forks.print, NULL);
	philo->live = pthread_mutex_init(&philo->forks.live, NULL);
	if (philo->print || philo->live)
		return (free_all(philo), 0);
	while (++i < philo->infos[0])
	{
		philo->number_of_mutex = i;
		if (pthread_mutex_init(&philo->forks.mutex[i], NULL))
			return (free_all(philo), 0);
		philo->brains[i].alive = &philo->alive;
		philo->brains[i].forks = &philo->forks;
		philo->brains[i].num = i;
		philo->brains[i].times = &philo->times;
		philo->brains[i].right_fork = philo->forks.mutex[i];
		if (i == 0)
			philo->brains[i].left_fork = philo->forks.mutex[philo->infos[0] - 1];
		else
			philo->brains[i].left_fork = philo->forks.mutex[i - 1];
	}
	return (1);
}

int	create_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->infos[0])
	{
		philo->number_of_philos = i;
		if (pthread_create(&philo->brains[i].philo, NULL
			, philo->route[philo->philo_rout[i]], &philo->brains[i]))
			return (free_all(philo), 0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	memset(&philo, 0, sizeof(philo));
	if (!check_in(argc, argv, &philo))
		return (1);
	if (!set_routine(&philo))
		return (1);
	if (!create_mutex(&philo))
		return (1);
	if (!create_thread(&philo))
		return (1);
	sleep(5);
	free_all(&philo);
	pthread_mutex_destroy(&philo.forks.live);
	pthread_mutex_destroy(&philo.forks.print);
	return (0);
}
