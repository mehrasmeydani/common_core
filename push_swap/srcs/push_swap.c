/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:28:59 by codespace         #+#    #+#             */
/*   Updated: 2025/05/08 09:30:08 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static ssize_t	find_case(t_stack *b)
{
	while (b)
	{
		if (b->opt != -1)
			break ;
		b = b->next;
	}
	if (b->opt == b->d_uu)
		return (1);
	if (b->opt == b->d_dd)
		return (2);
	if (b->opt == b->d_ud)
		return (3);
	if (b->opt == b->d_du)
		return (4);
	return (0);
}

static void	turn_till_opt(t_stack **a, t_stack **b, ssize_t c)
{
	if (c == 1)
		uu(a, b);
	else if (c == 2)
		dd(a, b);
	else if (c == 3)
		ud(a, b);
	else if (c == 4)
		du(a, b);
}

static ssize_t	is_sorted(t_stack *a)
{
	while (a && a->next)
	{
		if (a->num > a->next->num)
			return (0);
		a = a->next;
	}
	return (1);
}

static void	find_top(t_stack **a)
{
	t_stack	*tmp;
	ssize_t	i;

	tmp = *a;
	i = -1;
	while (tmp->num != 0)
		tmp = tmp->next;
	if (tmp->d_up > tmp->d_down)
		while (++i < tmp->d_down)
			rr(a, NULL, "rra");
	else
		while (++i < tmp->d_up)
			r(a, NULL, "ra");
}

void	sort_3(t_stack **a)
{
	if (is_sorted(*a))
		return ;
	if ((*a)->num == 1 && (*a)->next->num == 2)
		return (rr(a, NULL, "rra"));
	if ((*a)->num == 2)
		return (r(a, NULL, "ra"), sort_3(a));
	if ((*a)->num == 0 || (*a)->num == 1)
		return (s(a, NULL, "sa"), sort_3(a));
}

void	push_swap(t_stack **a, t_stack **b, ssize_t size)
{
	ssize_t	pushed;
	ssize_t	c;

	pushed = 0;
	c = 0;
	if (size == 3)
		return(sort_3(a));
	while ((!is_sorted(*a) && pushed == 0) || size != ft_stacksize(*a))
	{
		set_d(*a, *b);
		if (pushed == 0)
		{
			push_b_nonlis(a, b);
			pushed = 1;
			continue ;
		}
		set_opt(*a, *b);
		c = find_case(*b);
		turn_till_opt(a, b, c);
		p(a, b, "pa");
	}
	set_d(*a, *b);
	find_top(a);
}
