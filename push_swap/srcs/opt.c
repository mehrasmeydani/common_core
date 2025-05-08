/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:41:53 by codespace         #+#    #+#             */
/*   Updated: 2025/05/08 08:16:50 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

t_stack	*find_opt(t_stack *a, t_stack *b)
{
	t_stack	*tmp;

	tmp = a;
	if ((b->num > ft_stacklast(a)->num && b->num < a->num)
		|| (b->num < min(a) && a->num == min(a))
		|| (b->num > max(a) && ft_stacklast(a)->num == max(a)))
		return (a);
	while (a && a->next)
	{
		if ((b->num < a->next->num && a->next->num == min(tmp))
			|| ((a->num == max(tmp)) && (b->num > a->num))
			|| (b->num < a->next->num && (b->num > a->num)))
			break ;
		a = a->next;
	}
	return (a->next);
}

static void	set_moves(t_stack *b, t_stack *opt)
{
	ssize_t	min;

	b->d_uu = ((b->d_up >= opt->d_up) * b->d_up
			+ (b->d_up < opt->d_up) * opt->d_up);
	min = b->d_uu;
	b->d_dd = ((b->d_down >= opt->d_down) * b->d_down
			+ (b->d_down < opt->d_down) * opt->d_down);
	if (b->d_dd < min)
		min = b->d_dd;
	b->d_ud = opt->d_up + b->d_down;
	if (b->d_ud < min)
		min = b->d_ud;
	b->d_du = opt->d_down + b->d_up;
	if (b->d_du < min)
		min = b->d_du;
	b->d_opt = min;
}

void	set_opt(t_stack *a, t_stack *b)
{
	t_stack	*opt;
	t_stack	*tmp;
	ssize_t	min;
	ssize_t	num;

	min = -1;
	num = -1;
	tmp = b;
	while (b)
	{
		if (min != -1 && (b->d_up > min && b->d_down > min))
		{
			b = b->next;
			continue ;
		}
		opt = find_opt(a, b);
		set_moves(b, opt);
		if (num == -1 || min > b->d_opt)
		{
			num = b->num;
			min = b->d_opt;
			if (min == 0)
				break ;
		}
		b = b->next;
	}
	while (tmp)
	{
		tmp->opt = (num == tmp->num) * min + -1 * (num != tmp->num);
		tmp = tmp->next;
	}
}
