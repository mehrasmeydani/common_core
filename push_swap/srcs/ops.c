/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:38:03 by codespace         #+#    #+#             */
/*   Updated: 2025/05/08 08:11:34 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static void	swap(t_stack **a)
{
	t_stack	*tmp;

	tmp = (*a)->next;
	(*a)->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = (*a);
	tmp->next = (*a);
	tmp->prev = (*a)->prev;
	(*a)->prev = tmp;
	(*a) = tmp;
}

void	s(t_stack **a, t_stack **b, char *c)
{
	if (c[1] == 'a')
	{
		if (!*a || !(*a)->next)
			return ;
		swap(a);
	}
	if (c[1] == 'b')
	{
		if (!*b || !(*b)->next)
			return ;
		swap(b);
	}
	if (c[1] == 's')
	{
		s(a, b, " a");
		s(a, b, " b");
	}
	if (c[0] != ' ')
		ft_putendl_fd(c, 1);
}

static void	push(t_stack **a, t_stack **b)
{
	t_stack	*tmp;

	tmp = (*a)->next;
	(*a)->next = *b;
	if (*b)
		(*b)->prev = (*a);
	*b = *a;
	if (tmp)
	{
		tmp->prev = NULL;
	}
	*a = tmp;
}

void	p(t_stack **a, t_stack **b, char *c)
{
	if (c[1] == 'a')
	{
		if (!*b)
			return ;
		push(b, a);
	}
	if (c[1] == 'b')
	{
		if (!*a)
			return ;
		push(a, b);
	}
	ft_putendl_fd(c, 1);
}
