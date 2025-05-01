/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:21 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 13:19:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>

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
	in->size = i[2] + 1;
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

t_stack	*make_stack(t_ps *in)
{
	t_stack	*new;
	t_stack	*out;
	ssize_t	i;

	i = -1;
	out = NULL;
	while (++i < in->size)
	{
		new = ft_stacknew(in, i);
		if (!new)
			return (ft_stackclear(&out), NULL);
		ft_stackadd_back(&out, new);
	}
	return (out);
}

bool	check(t_ps *in)
{
	tol(in);
	ft_free(in->out, ft_strstrlen(in->out));
	if (!in->num)
		return (0);
	ft_sort_long_tab(in->sorted, in->size);
	reset_values(in);
	set_lis(in);
	return (1);
}

int	main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (1);
	init(&ps);
	ps.in = ft_splits((ssize_t)(argc - 1), &argv[1]);
	ft_nums(&ps);
	if (!ps.out)
		return (ft_free_free(ps.in, ft_strstrstrlen(ps.in)), 1);
	if (!check(&ps))
		return (1);
	a = make_stack(&ps);
	free(ps.lis);
	free(ps.idx);
	b = NULL;
	(void)b;
	ft_stackclear(&a);
}

	//ft_free_free(ps.in, ft_strstrstrlen(ps.in));
	//free(ps.num);
	//push_swap(&ps, &a, &b);