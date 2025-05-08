/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:21:55 by codespace         #+#    #+#             */
/*   Updated: 2025/05/08 06:34:06 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static bool	valid(char *in)
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

static void	tol(t_ps *in)
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
		while (++j <= i)
			if ((in->num[j] == in->num[i] && i != j) || in->num[i] > 2147483647
				|| in->num[i] < -2147483648 || !valid(in->out[i]))
				return (free(in->num), (void)(in->num = NULL),
						free(in->sorted), ft_putendl_fd("Error", 2));
		in->sorted[i] = in->num[i];
	}
}

static void	reset_values(t_ps *in)
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
