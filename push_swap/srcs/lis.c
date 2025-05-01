/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:00:19 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 12:21:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static void	rotate(ssize_t *list, ssize_t size)
{
	ssize_t	tmp;
	ssize_t	i;

	tmp = list[0];
	i = -1;
	while (++i < size - 1)
		list[i] = list[i + 1];
	list[size - 1] = tmp;
}

static ssize_t	search_place(ssize_t *lis, ssize_t new, ssize_t size)
{
	ssize_t	i;

	i = -1;
	while (lis[++i] != -1 && i < size && lis[i] < new)
		;
	if (lis[i] == -1)
		return (lis[i] = new, i);
	return (lis[i] = new, i);
}

static ssize_t	lis(t_ps *in)
{
	ssize_t	i;
	ssize_t	max;
	ssize_t	best;

	i = -1;
	max = -1;
	while (++i < in->size)
	{
		in->lis[i] = search_place(in->lis_util2, in->lis_util[i], in->size);
		if (in->lis[i] > max)
			max = in->lis[i];
	}
	i = -1;
	best = max;
	while (++i < in->size)
	{
		if (in->lis[in->size - i - 1] == max)
		{
			in->lis[in->size - i - 1] = 1;
			max--;
		}
		else
			in->lis[in->size - i - 1] = 0;
	}
	return (best);
}

static ssize_t	best_lis(t_ps *in)
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
		ft_memset(in->lis, -1, in->size * sizeof(ssize_t));
		ft_memset(in->lis_util2, -1, in->size * sizeof(ssize_t));
		tmp = lis(in);
		if (tmp > max)
		{
			max = tmp;
			out = in->lis_util[0];
		}
		rotate(in->lis_util, in->size);
	}
	return (out);
}

void	set_lis(t_ps *in)
{
	ssize_t	best;

	best = best_lis(in);
	while (in->lis_util[0] != best)
		rotate(in->lis_util, in->size);
	lis(in);
	while (in->lis_util[0] != in->idx[0])
	{
		rotate(in->lis_util, in->size);
		rotate(in->lis, in->size);
	}
}
