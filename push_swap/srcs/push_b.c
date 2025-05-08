/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:32:13 by codespace         #+#    #+#             */
/*   Updated: 2025/05/08 09:25:39 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static void	push_b_nonlisr(t_stack **a, t_stack **b)
{
	t_stack	*tmp;
	ssize_t	lis_count;

	tmp = *a;
	lis_count = 0;
	while (tmp)
	{
		if (tmp->lis == 1)
			lis_count++;
		tmp = tmp->next;
	}
	while (ft_stacksize(*a) != lis_count)
	{
		if ((*a)->lis == 0)
			p(a, b, "pb");
		else
			r(a, b, "ra");
	}
}

static void	push_b_nonlisrr(t_stack **a, t_stack **b)
{
	t_stack	*tmp;
	ssize_t	lis_count;

	tmp = *a;
	lis_count = 0;
	while (tmp)
	{
		if (tmp->lis)
			lis_count++;
		tmp = tmp->next;
	}
	while (ft_stacksize(*a) != lis_count)
	{
		if ((*a)->lis == 0)
			p(a, b, "pb");
		else
			rr(a, b, "rra");
	}
}

void	push_b_nonlis(t_stack **a, t_stack **b)
{
	t_stack	*tmp;
	ssize_t	max_dr;
	ssize_t	max_drr;

	max_dr = 0;
	max_drr = -1;
	tmp = *a;
	while (tmp)
	{
		if (tmp->lis == 1)
		{
			if (max_drr == -1)
				max_drr = tmp->d_down;
			max_dr += 1;
		}
		else if (max_dr > 0)
			max_dr -= 1;
		tmp = tmp->next;
	}
	if (max_dr > max_drr)
		push_b_nonlisrr(a, b);
	else
		push_b_nonlisr(a, b);
}
