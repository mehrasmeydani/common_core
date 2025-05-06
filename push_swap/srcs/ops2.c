/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:25:58 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 11:26:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static void	rotate(t_stack **a)
{
	t_stack	*tmp;

	tmp = (*a)->next;
	(*a)->prev = ft_stacklast(*a);
	ft_stacklast(*a)->next = *a;
	(*a)->next = NULL;
	tmp->prev = NULL;
	*a = tmp;
}

void	r(t_stack **a, t_stack **b, char *c)
{
	if (c[1] == 'a')
	{
		if (!*a || !(*a)->next)
			return ;
		rotate(a);
	}
	if (c[1] == 'b')
	{
		if (!*b || !(*b)->next)
			return ;
		rotate(b);
	}
	if (c[1] == 'r')
	{
		r(a, b, " a");
		r(a, b, " b");
	}
	if (c[0] != ' ')
		ft_putendl_fd(c, 1);
}

static void	rrotate(t_stack **a)
{
	t_stack	*tmp;

	tmp = ft_stacklast(*a)->prev;
	(*a)->prev = ft_stacklast(*a);
	ft_stacklast(*a)->next = *a;
	tmp->next->prev = NULL;
	tmp->next = NULL;
	*a = (*a)->prev;
}

void	rr(t_stack **a, t_stack **b, char *c)
{
	if (c[2] == 'a')
	{
		if (!*a || !(*a)->next)
			return ;
		rrotate(a);
	}
	if (c[2] == 'b')
	{
		if (!*b || !(*b)->next)
			return ;
		rrotate(b);
	}
	if (c[2] == 'r')
	{
		rr(a, b, "  a");
		rr(a, b, "  b");
	}
	if (c[0] != ' ')
		ft_putendl_fd(c, 1);
}
