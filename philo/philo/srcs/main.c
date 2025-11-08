/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:24:44 by megardes          #+#    #+#             */
/*   Updated: 2025/11/08 21:42:56 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	my_usleep(t_thinker *philo, unsigned int time, unsigned int life,
	unsigned int last_meal)
{
	unsigned int	current_time;
	unsigned int	pass_time;

	current_time = my_time();
	pass_time = my_time();
	while (time && (current_time - pass_time < time || time == life))
	{
		if (current_time - last_meal > life + 2)
		{
			ml(&philo->forks->live);
			if (*philo->alive != -1)
				return (mu(&philo->forks->live), 1);
			*philo->alive = philo->num;
			mu(&philo->forks->live);
			return (1);
		}
		current_time = my_time();
		usleep(25);
	}
	return (0);
}

void	*start(void *in)
{
	t_thinker *philo;

	philo = (t_thinker *)in;
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
			philo->first = my_time();
			if (philo->number_of_philos % 2 == 0 && philo->num % 2 == 1 && philo->times.eat == philo->times.sleep)
				usleep(philo->times.eat / 2 * 100);
			philo->last_meal = my_time();
			break ;
		}
		mu(&philo->forks->start);
		usleep(1);
	}
	return (philo->f(in));
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

int	take_fork2(t_thinker *philo, bool fork_stat)
{
	if (fork_stat == 0)
	{
		ml(philo->right_fork);
		if (thinker_print(philo, philo->first,
				philo->num, "has taken a fork"))
			return (mu(philo->right_fork), 0);
		ml(philo->left_fork);
		if (thinker_print(philo, philo->first,
				philo->num, "has taken a fork"))
			return (mu(philo->left_fork), mu(philo->right_fork), 0);
	}
	else
	{
		mu(philo->left_fork);
		mu(philo->right_fork);
	}
	return (1);
}

int	take_fork(t_thinker *philo, bool fork_stat)
{
	if (philo->last_philo)
	{
		if (fork_stat == 0)
		{
			ml(philo->left_fork);
			if (thinker_print(philo, philo->first,
					philo->num, "has taken a fork"))
				return (mu(philo->left_fork), 0);
			ml(philo->right_fork);
			if (thinker_print(philo, philo->first,
					philo->num, "has taken a fork"))
				return (mu(philo->right_fork), mu(philo->left_fork), 0);
		}
		else
		{
			mu(philo->right_fork);
			mu(philo->left_fork);
		}
		return (1);
	}
	return (take_fork2(philo, fork_stat));
}

void	*my_eat(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
	if (philo->number_of_philos == 1)
		return (spaghetti_needs_two(philo));
	if (!take_fork(philo, 0))
		return (NULL);
	philo->last_meal = my_time();
	if (thinker_print(philo, philo->first, philo->num, "is eating"))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	if (my_usleep(philo, philo->times.eat, philo->times.life, philo->last_meal))
		return (mu(philo->right_fork), mu(philo->left_fork), NULL);
	if (!take_fork(philo, 1))
		return (NULL);
	if (philo->times.must_eat != 0 && check_meals(philo))
		return (NULL);
	my_sleep(in);
	return (NULL);
}

void	*my_sleep(void *in)
{
	t_thinker	*philo;

	philo = (t_thinker *)in;
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
	if (thinker_print(philo, philo->first, philo->num, "is thinking"))
		return (NULL);
	if (my_usleep(philo, philo->times.think, philo->times.life,
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
	if (philo->infos[0] % 2)
		philo->philo_rout[i - 1] += 1;
	philo->route[0] = my_eat;
	philo->route[1] = my_think;
	philo->route[2] = my_sleep;
	return (1);
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
	while (++i < philo->infos[0])
		if (!set_brains(philo, i))
			return (0);
	philo->print_mutex = pthread_mutex_init(&philo->forks.print, NULL);
	philo->alive_mutex = pthread_mutex_init(&philo->forks.live, NULL);
	philo->done_mutex = pthread_mutex_init(&philo->forks.done, NULL);
	pthread_mutex_init(&philo->forks.start, NULL);
	pthread_mutex_init(&philo->forks.here, NULL);
	if (philo->print_mutex || philo->alive_mutex || philo->done_mutex)
		return (free_all(philo), 0);
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
			philo->start = my_time();
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
			ml(&philo->forks.print);
			printf("%u %d %s\n", (my_time() - philo->start) / 10, philo->living, "died");
			mu(&philo->forks.print);
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
		philo->brains[i].first = my_time();
		philo->brains[i].last_meal = philo->brains[i].first;
		philo->brains[i].f = philo->route[philo->philo_rout[i]];
		if (i == philo->infos[0] - 1)
			philo->brains[i].last_philo = 1;
		if (pthread_create(&philo->brains[i].philo, NULL,
				start, &philo->brains[i]))
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
