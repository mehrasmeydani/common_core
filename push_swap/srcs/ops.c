/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:38:03 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 15:11:20 by codespace        ###   ########.fr       */
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
		swap(a);
	if (c[1] == 'b')
		swap(b);
	if (c[1] == 's')
	{
		s(a, b, "sa");
		s(a, b, "sb");
	}
	//ft_putendl_fd(c, 1);
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
		push(b, a);
	if (c[1] == 'b')
		push(a, b);
	//ft_putendl_fd(c, 1);
}

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
		rotate(a);
	if (c[1] == 'b')
		rotate(b);
	if (c[1] == 'r')
	{
		r(a, b, "ra");
		r(a, b, "rb");
	}
	//ft_putendl_fd(c, 1);
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
		rrotate(a);
	if (c[2] == 'b')
		rrotate(b);
	if (c[2] == 'r')
	{
		rr(a, b, "rra");
		rr(a, b, "rrb");
	}
	//ft_putendl_fd(c, 1);
}