/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/08/06 02:04:25 by megardes         ###   ########.fr       */
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
		if (((argv[argc][0] != '+' || argv[argc]++) && !ft_isdigit(argv[argc]))
			|| argv[argc][0] == '0')
			return (ft_put_str("Argument ", 2), ft_putnbr(argc, 2),
				ft_put_endl(": is not a valid number", 2), 0);
		else
			philo->infos[argc - 1] = not_atoi(argv[argc]);
	}
	philo->times.life = philo->infos[1];
	philo->times.eat = philo->infos[2];
	philo->times.sleep = philo->infos[3];
	philo->times.think = philo->infos[1] - philo->infos[2] - philo->infos[3];
	//philo->times.think -= 5;
	if (philo->infos[4] != -1)
			philo->times.must_eat = philo->infos[4];
	return (1);
}

int	my_time(t_thinker *philo)
{
	if (gettimeofday(&philo->time, NULL))
		return (1);
	philo->current_time = (unsigned int)philo->time.tv_usec / 1000+ (philo->time.tv_sec % 10000 * 1000);
	return (0);
}

int	my_time2(unsigned int *in)
{
	t_tm	time;

	if (gettimeofday(&time, NULL))
		return (1);
	*in = (unsigned int)time.tv_usec / 1000 + (time.tv_sec % 10000 * 1000);
	return (0);
}

unsigned int	my_time3(void)
{
	t_tm	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((unsigned int)time.tv_usec / 1000 + (time.tv_sec % 10000 * 1000));
}

void	god_print(t_philo *philo, unsigned int time, int num, char *action)
{
	pthread_mutex_lock(&philo->forks.print);
	printf("%d %d %s\n", time, num, action);
	pthread_mutex_unlock(&philo->forks.print);
}

int	thinker_print(t_thinker *philo, unsigned int time, int num, const char *action)
{
	my_time(philo);
	(void)action;
	pthread_mutex_lock(&philo->forks->print);
	pthread_mutex_lock(&philo->forks->live);
	if (*philo->alive)
		return (pthread_mutex_unlock(&philo->forks->live)
			, pthread_mutex_unlock(&philo->forks->print), 1);
	pthread_mutex_unlock(&philo->forks->live);
	printf("%u %d %s\n", philo->current_time - time, num, action);
	pthread_mutex_unlock(&philo->forks->print);
	return (0);
}

int	my_usleep(t_thinker *philo, unsigned int time, unsigned int life, unsigned int last_meal)
{
	unsigned int	current_time;
	unsigned int	pass_time;

	current_time = my_time3();
	pass_time = my_time3();
	while (current_time - pass_time < time)
	{
		current_time = my_time3();
		if (current_time - last_meal > life)
		{
			pthread_mutex_lock(&philo->forks->live);
			*philo->alive = philo->num;
			pthread_mutex_unlock(&philo->forks->live);
			return (1);
		}
		usleep(500);
	}
	return (0);
}

void	*my_eat(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	pthread_mutex_lock(&philo->left_fork);
	if (thinker_print(philo, philo->first, philo->num, "taken a fork"))
		return (pthread_mutex_unlock(&philo->left_fork), NULL);
	pthread_mutex_lock(&philo->right_fork);
	if (thinker_print(philo, philo->first, philo->num, "taken a fork"))
		return (pthread_mutex_unlock(&philo->right_fork)
			, pthread_mutex_unlock(&philo->left_fork), NULL);
	if (thinker_print(philo, philo->first, philo->num, "is eating"))
		return (pthread_mutex_unlock(&philo->right_fork)
			, pthread_mutex_unlock(&philo->left_fork), NULL);
	philo->last_meal = my_time3();
	if (my_usleep(philo, philo->times.eat, philo->times.life, philo->last_meal))
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_lock(&philo->forks->done);
	philo->meals++;
	if (philo->meals == philo->times.must_eat)
		return (pthread_mutex_unlock(&philo->forks->done), NULL);
	pthread_mutex_unlock(&philo->forks->done);
	my_sleep(in);
	return (NULL);
}

void	*my_sleep(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (thinker_print(philo, philo->first, philo->num, "is sleeping"))
		return (NULL);
	if (my_usleep(philo, philo->times.sleep, philo->times.life, philo->last_meal))
		return (NULL);
	my_think(in);
	return (NULL);
}

void	*my_think(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (thinker_print(philo, philo->first, philo->num, "is thinking"))
		return (NULL);
	if (my_usleep(philo, 0 , philo->times.life, philo->last_meal))
		return (NULL);
	my_eat(in);
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
	philo->print_mutex = pthread_mutex_init(&philo->forks.print, NULL);
	philo->alive_mutex = pthread_mutex_init(&philo->forks.live, NULL);
	philo->done_mutex = pthread_mutex_init(&philo->forks.done, NULL);
	if (philo->print_mutex || philo->alive_mutex || philo->done_mutex)
		return (free_all(philo), 0);
	while (++i < philo->infos[0])
	{
		philo->number_of_mutex = i;
		if (pthread_mutex_init(&philo->forks.mutex[i], NULL))
			return (free_all(philo), 0);
		philo->brains[i].alive = &philo->living;
		philo->brains[i].forks = &philo->forks;
		philo->brains[i].num = i;
		philo->brains[i].times = philo->times;
		philo->brains[i].right_fork = philo->forks.mutex[i];
		if (i == 0)
			philo->brains[i].left_fork = philo->forks.mutex[philo->infos[0] - 1];
		else
			philo->brains[i].left_fork = philo->forks.mutex[i - 1];
	}
	return (1);
}

void	*god_work(void *in)
{
	t_philo				*philo;
	t_thinker			brain;
	unsigned int		num;
	int					i;	

	philo = (t_philo *)in;
	while (true)
	{
		i = 0;
		pthread_mutex_lock(&philo->forks.done);
		while (i < philo->infos[0] && philo->times.must_eat == philo->brains[i].meals)
			i++;
		pthread_mutex_unlock(&philo->forks.done);
		if (i == philo->infos[0])
			return (NULL);
		pthread_mutex_lock(&philo->forks.live);
		if (philo->living != 0)
		{
			num = philo->living;
			brain = philo->brains[num];
			my_time(&brain);
			god_print(philo, (brain.current_time - brain.first)
				, num, "died");
			pthread_mutex_unlock(&philo->forks.live);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->forks.live);
	}
}

int	create_thread(t_philo *philo)
{
	int	i;

	i = -1;
	if (pthread_create(&philo->omnipotent, NULL, god_work, philo))
		return (free_all(philo), 0);
	while (++i < philo->infos[0])
	{
		philo->number_of_philos = i;
		my_time(&philo->brains[i]);
		philo->brains[i].first = philo->brains[i].current_time;
		philo->brains[i].last_meal = philo->brains[i].first;
		if (pthread_create(&philo->brains[i].philo, NULL
			, philo->route[philo->philo_rout[i]], &philo->brains[i]))
			return (free_all(philo), 0);
	}
	pthread_join(philo->omnipotent, NULL);
	i = -1;
	while (++i < philo->number_of_philos)
		pthread_join(philo->brains[i].philo, NULL);
	free(philo->brains);
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
	free_all(&philo);
	return (0);
}
