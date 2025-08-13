/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/08/13 17:58:55 by megardes         ###   ########.fr       */
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
	philo->times.life = philo->infos[1] * 10;
	philo->times.eat = philo->infos[2] * 10;
	philo->times.sleep = philo->infos[3] * 10;
	philo->times.think = (philo->infos[1] - philo->infos[2] - philo->infos[3]) * 10;
	if (philo->infos[4] != -1)
		philo->times.must_eat = philo->infos[4];
	return (1);
}

unsigned int	my_time3(void)
{
	t_tm	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((unsigned int)time.tv_usec / 100 + (time.tv_sec % 100000 * 10000));
}

void	god_print(t_philo *philo, unsigned int time, int num, char *action)
{
	ml(&philo->forks.print);
	printf("%d %d %s\n", time / 10, num, action);
	mu(&philo->forks.print);
}

int	thinker_print(t_thinker *philo, unsigned int time, int num,
	const char *action)
{
	ml(&philo->forks->live);
	ml(&philo->forks->print);
	if (*philo->alive != -1)
		return (mu(&philo->forks->live), mu(&philo->forks->print), 1);
	else if (my_time3() - philo->last_meal > philo->times.life + 9)
		return (*philo->alive = philo->num, mu(&philo->forks->live),
			mu(&philo->forks->print), philo->death = my_time3(), 1);
	mu(&philo->forks->live);
	printf("%u %d %s\n", (my_time3() - time) / 10, num, action);
	mu(&philo->forks->print);
	return (0);
}

int	my_usleep(t_thinker *philo, unsigned int time, unsigned int life,
	unsigned int last_meal)
{
	unsigned int	current_time;
	unsigned int	pass_time;

	current_time = my_time3();
	pass_time = my_time3();
	while (current_time - pass_time < time || time < 10 || time == life)
	{
		current_time = my_time3();
		if (time < 10)
		{
			usleep(philo->times.think * 50);
			break ;
		}
		if (current_time - last_meal > life + 9)
		{
			ml(&philo->forks->live);
			*philo->alive = philo->num;
			philo->death = my_time3();
			mu(&philo->forks->live);
			return (1);
		}
		usleep(200);
	}
	return (0);
}

void	start(t_thinker *philo)
{
	philo->start = 1;
	ml(&philo->forks->here);
	*philo->all_here = *philo->all_here + 1;
	mu(&philo->forks->here);
	while (true)
	{
		ml(&philo->forks->start);
		if (*philo->start_god)
		{
			mu(&philo->forks->start);
			philo->first = my_time3();
			philo->last_meal = my_time3();
			break ;
		}
		mu(&philo->forks->start);
		usleep(1);
	}
}

int	check_meals(t_thinker *philo)
{
	ml(&philo->forks->done);
	if (philo->meals < philo->times.must_eat)
	{
		philo->meals++;
		*(philo->all_meals) = *(philo->all_meals) + 1;
	}
	if (*philo->all_meals == philo->number_of_philos * philo->times.must_eat)
		return (mu(&philo->forks->done), 1);
	mu(&philo->forks->done);
	return (0);
}

void	*spaghetti_needs_two(t_thinker *philo)
{
	ml(philo->left_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->left_fork), NULL);
	if (my_usleep(philo, philo->times.life, philo->times.life, philo->last_meal))
		return (mu(philo->left_fork), NULL);
	return (NULL);
}

void	*my_eat(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->start)
		start(philo);
	if (philo->number_of_philos == 1)
		return (spaghetti_needs_two(philo));
	ml(philo->left_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->left_fork), NULL);
	ml(philo->right_fork);
	if (thinker_print(philo, philo->first, philo->num, "has taken a fork"))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	if (thinker_print(philo, philo->first, philo->num, "is eating"))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	philo->last_meal = my_time3();
	if (my_usleep(philo, philo->times.eat, philo->times.life, philo->last_meal))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	mu(philo->right_fork);
	mu(philo->left_fork);
	if (philo->times.must_eat != 0 && check_meals(philo))
		return (NULL);
	my_sleep(in);
	return (NULL);
}

void	*my_sleep(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->start)
		start(philo);
	if (thinker_print(philo, philo->first, philo->num, "is sleeping"))
		return (NULL);
	if (my_usleep(philo, philo->times.sleep, philo->times.life,
			philo->last_meal))
		return (NULL);
	if (philo->times.must_eat != 0)
	{	
		ml(&philo->forks->done);
		if (*philo->all_meals == philo->number_of_philos * philo->times.must_eat)
			return (mu(&philo->forks->done), NULL);
		mu(&philo->forks->done);
	}
	my_think(in);
	return (NULL);
}

void	*my_think(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (!philo->start)
		start(philo);
	if (thinker_print(philo, philo->first, philo->num, "is thinking"))
		return (NULL);
	if (my_usleep(philo, philo->times.think / 2, philo->times.life,
			philo->last_meal))
		return (NULL);
	if (philo->times.must_eat != 0)
	{	
		ml(&philo->forks->done);
		if (*philo->all_meals == philo->number_of_philos * philo->times.must_eat)
			return (mu(&philo->forks->done), NULL);
		mu(&philo->forks->done);
	}
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
						|| (y == len - 1 && philo[y - 1] != philo[y]
							&& philo[0] != philo[y])))
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
	philo->philo_rout = (int *)not_calloc(philo->infos[0], sizeof(int));
	if (!philo->philo_rout)
		return (0);
	while (++i < philo->infos[0])
		philo->philo_rout[i] = i % 2;
	i = 0;
	set_recur(0, philo->philo_rout, philo->infos[0], (bool *)(&i));
	philo->route[0] = my_eat;
	philo->route[1] = my_think;
	philo->route[2] = my_sleep;
	return (i);
}

int	set_brains(t_philo *philo, int i)
{
	philo->number_of_mutex = i;
	if (pthread_mutex_init(&philo->forks.mutex[i], NULL))
		return (free_all(philo), 0);
	philo->brains[i].number_of_philos = philo->infos[0];
	philo->brains[i].alive = &philo->living;
	philo->brains[i].forks = &philo->forks;
	philo->brains[i].num = i;
	philo->brains[i].times = philo->times;
	philo->brains[i].all_meals = &philo->all_meals;
	philo->brains[i].all_here = &philo->all_here;
	philo->brains[i].start_god = &philo->start;
	philo->brains[i].right_fork = &philo->forks.mutex[i];
	if (i == 0)
		philo->brains[i].left_fork = &philo->forks.mutex[philo->infos[0] - 1];
	else
		philo->brains[i].left_fork = &philo->forks.mutex[i - 1];
	return (1);
}

int	create_mutex(t_philo *philo)
{
	int	i;

	philo->brains = (t_thinker *)calloc(philo->infos[0], sizeof(t_thinker));
	philo->forks.mutex = (t_mutex *)calloc(philo->infos[0], sizeof(t_mutex));
	if (!philo->brains || !philo->forks.mutex)
		return (free_all(philo), 0);
	i = -1;
	philo->living = -1;
	philo->print_mutex = pthread_mutex_init(&philo->forks.print, NULL);
	philo->alive_mutex = pthread_mutex_init(&philo->forks.live, NULL);
	philo->done_mutex = pthread_mutex_init(&philo->forks.done, NULL);
	pthread_mutex_init(&philo->forks.start, NULL);
	pthread_mutex_init(&philo->forks.here, NULL);
	if (philo->print_mutex || philo->alive_mutex || philo->done_mutex)
		return (free_all(philo), 0);
	while (++i < philo->infos[0])
		if (!set_brains(philo, i))
			return (0);
	return (1);
}

void	god_first(t_philo *philo)
{
	while (true)
	{
		ml(&philo->forks.here);
		if (philo->all_here == (unsigned int)philo->infos[0])
		{
			ml(&philo->forks.start);
			philo->start = 1;
			mu(&philo->forks.start);
			mu(&philo->forks.here);
			break ;
		}
		mu(&philo->forks.here);
		usleep(1);
	}
}

void	*god_work(void *in)
{
	t_philo				*philo;
	t_thinker			brain;
	unsigned int		num;	

	philo = (t_philo *)in;
	god_first(philo);
	while (true)
	{
		if (philo->infos[4] != -1)
		{	
			ml(&philo->forks.done);
			if (philo->all_meals == philo->infos[0] * philo->times.must_eat)
				return (mu(&philo->forks.done), NULL);
			mu(&philo->forks.done);
		}
		ml(&philo->forks.live);
		if (philo->living != -1)
		{
			num = philo->living;
			brain = philo->brains[num];
			god_print(philo, (brain.death - brain.first), num, "died");
			mu(&philo->forks.live);
			return (NULL);
		}
		mu(&philo->forks.live);
		usleep(1);
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
		philo->brains[i].first = my_time3();
		philo->brains[i].last_meal = philo->brains[i].first;
		if (pthread_create(&philo->brains[i].philo, NULL,
				philo->route[philo->philo_rout[i]], &philo->brains[i]))
			return (free_all(philo), 0);
	}
	pthread_join(philo->omnipotent, NULL);
	i = -1;
	while (++i < philo->number_of_philos + 1)
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
