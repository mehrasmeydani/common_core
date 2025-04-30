/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:21 by codespace         #+#    #+#             */
/*   Updated: 2025/04/30 20:04:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>

long	ft_atol(const char *nptr)
{
	long	out;
	ssize_t	j;
	long	sign;

	out = 0;
	j = -1;
	sign = 1;
	while (nptr[++j] == 32 || (nptr[j] >= 9 && nptr[j] <= 13))
		;
	if ((nptr[j] == '-' || nptr[j] == '+') && ++j)
		if (nptr[j - 1] == '-')
			sign = -1;
	while (nptr[j] >= '0' && nptr[j] <= '9')
		out = out * 10 + nptr[j++] - '0';
	return (out * sign);
}

void	ft_nums(t_ps *in)
{
	ssize_t	i[3];

	i[0] = 0;
	i[1] = -1;
	if (!in || !in->in)
		return ;
	while (in->in[++(i[1])])
		i[0] += ft_strstrlen(in->in[i[1]]);
	in->out = (char **)malloc((i[0] + 1) * sizeof(char *));
	if (!in->out)
		return ;
	in->out[i[0]] = NULL;
	i[2] = -1;
	i[1] = -1;
	while (in->in[++i[1]])
	{
		i[0] = -1;
		while (in->in[i[1]][++i[0]] && ++i[2] > -1)
			in->out[i[2]] = in->in[i[1]][i[0]];
		free(in->in[i[1]]);
		in->in[i[1]] = NULL;
	}
	free(in->in);
	in->in = NULL;
	in->size = i[2];
}

bool	valid(char *in)
{
	int		sign;
	ssize_t	i;

	i = -1;
	sign = 0;
	while (in[++i])
	{
		if (!ft_isdigit(in[i]) && !(in[i] == '-' || in[i] == '+'))
			return (0);
		if (in[i] == '-' || in[i] == '+')
			sign++;
		if (sign > 1)
			return (0);
	}
	return (1);
}

void	tol(t_ps *in)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	in->num = (long *)malloc(sizeof(long) * in->size);
	in->sorted = (long *)malloc(sizeof(long) * in->size);
	in->lis = (ssize_t *)malloc(sizeof(ssize_t) * in->size);
	in->idx = (ssize_t *)malloc(sizeof(ssize_t) * in->size);
	in->lis_util = (ssize_t *)malloc(sizeof(ssize_t) * in->size);
	in->lis_util2 = (ssize_t *)malloc(sizeof(ssize_t) * in->size);
	if (!in->lis || !in->sorted || !in->num || !in->idx || !in->lis_util
		|| !in->lis_util2)
		return (free(in->sorted), free(in->num), free(in->lis), free(in->idx),
			free(in->lis_util), free(in->lis_util2), (void)(in->num = NULL));
	while (++i < in->size)
	{
		j = -1;
		in->num[i] = ft_atol(in->out[i]);
		while (++j < i)
			if (in->num[j] == in->num[i] || in->num[i] > 2147483647
				|| in->num[i] < -2147483648 || !valid(in->out[i]))
				return (free(in->num), (void)(in->num = NULL),
						free(in->sorted), ft_putendl_fd("Error", 2));
		in->sorted[i] = in->num[i];
	}
}

void	ft_swap(long *a, long *b)
{
	long	why;

	why = *a;
	*a = *b;
	*b = why;
}

void	reset_values(t_ps *in)
{
	ssize_t	j;
	ssize_t	i;

	i = -1;
	while (++i < in->size)
	{
		j = -1;
		while (++j < in->size)
		{
			if (in->sorted[i] == in->num[j])
			{
				in->idx[j] = i;
				in->lis[j] = i;
				in->lis_util[j] = i;
			}
		}
	}
	free(in->num);
	free(in->sorted);
}

void	ft_sort_long_tab(long *tab, ssize_t size)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (tab[j] < tab[i])
				ft_swap(&tab[j], &tab[i]);
	}
}

ssize_t	lis(ssize_t *arr, ssize_t n, ssize_t *max_ref)
{
	ssize_t	res;
	ssize_t	max_ending_here;
	ssize_t	i;

	res = 1;
	max_ending_here = 1;
	i = 1;
	if (n == 1)
		return (1);
	while (i < n)
	{
		res = lis(arr, i, max_ref);
		if (arr[i - 1] < arr[n - 1] && res + 1 > max_ending_here)
			max_ending_here = res + 1;
		i++;
	}
	if (*max_ref < max_ending_here)
		*max_ref = max_ending_here;
	return (max_ending_here);
}

ssize_t	do_lis(ssize_t *list, ssize_t n)
{
	ssize_t	max;

	max = 1;
	lis(list, n, &max);
	return (max);
}

void	rotate(ssize_t *list, ssize_t size)
{
	ssize_t	tmp;
	ssize_t	i;

	tmp = list[0];
	i = -1;
	while (++i < size - 1)
		list[i] = list[i + 1];
	list[size - 1] = tmp;
}

ssize_t	best_lis(t_ps *in)
{
	ssize_t	out;
	ssize_t	i;
	ssize_t	max;
	ssize_t	tmp;

	i = -1;
	out = -1;
	max = -1;
	while (++i < in->size)
	{
		tmp = do_lis(in->lis, in->size);
		if (tmp > max)
		{
			max = tmp;
			out = in->lis[0];
		}
		rotate(in->lis, in->size);
	}
	return (out);
}



ssize_t	search_place(ssize_t *lis, ssize_t new, ssize_t size)
{
	ssize_t	i;

	i = -1;
	while (lis[++i] != -1 && i < size && lis[i] < new)
		;
	if (lis[i] == -1)
		return (lis[i] = new, i);
	return (lis[i - 1] = new, i);
}

void	set_lis(t_ps *in, ssize_t best)
{
	ssize_t	i;
	ssize_t	max;

	i = -1;
	while (in->lis_util[0] != best)
		rotate(in->lis_util, in->size);
	max = do_lis(in->lis_util, in->size) - 1;
	while (++i < in->size)
		in->lis[i] = search_place(in->lis_util2, in->lis_util[i], in->size);
	i = -1;
	while (++i < in->size)
	{
		ft_putnbr_fd(in->lis[in->size - i - 1], 1);
		if (in->lis[in->size - i - 1] == max)
		{
			in->lis[in->size - i - 1] = 1;
			max--;
		}
		else
			in->lis[in->size - i - 1] = 0;
	}
	while (in->lis_util[0] != in->idx[0])
	{
		rotate(in->lis_util, in->size);
		rotate(in->lis, in->size);
	}
}

bool	check(t_ps *in, t_stack *a, t_stack *b)
{
	ssize_t	best;

	tol(in);
	ft_free(in->out, ft_strstrlen(in->out));
	if (!in->num)
		return (0);
	ft_sort_long_tab(in->sorted, in->size);
	reset_values(in);
	best = best_lis(in);
	ft_memset(in->lis, -1, in->size);
	ft_memset(in->lis_util2, -1, in->size);
	set_lis(in, best);
	best = -1;
	while (++best < in->size)
		ft_putnbr_fd(in->idx[best], 1), ft_putchar_fd(' ', 1);
	ft_putendl_fd("\n", 1);
	best = -1;
	while (++best < in->size)
		ft_putnbr_fd(in->lis_util[best], 1), ft_putchar_fd(' ', 1);
	ft_putendl_fd("\n", 1);
	best = -1;
	while (++best < in->size)
		ft_putnbr_fd(in->lis[best], 1), ft_putchar_fd(' ', 1);
	ft_putendl_fd("\n", 1);
	best = -1;
	while (++best < in->size)
		if (in->lis[best] == 1)
			ft_putnbr_fd(in->lis_util[best], 1), ft_putchar_fd(' ', 1);
	ft_putendl_fd("\n", 1);
	(void)a;
	(void)b;
	return (1);
}

int	main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	a;
	t_stack	b;

	if (argc < 2)
		return (1);
	init(&ps, &a, &b);
	ps.in = ft_splits((ssize_t)(argc - 1), &argv[1]);
	ft_nums(&ps);
	if (!ps.out)
		return (ft_free_free(ps.in, ft_strstrstrlen(ps.in)), 1);
	if (!check(&ps, &a, &b))
		return (1);
}

	//ft_free_free(ps.in, ft_strstrstrlen(ps.in));
	//free(ps.num);
	//push_swap(&ps, &a, &b);