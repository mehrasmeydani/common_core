/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:21 by codespace         #+#    #+#             */
/*   Updated: 2025/05/05 16:55:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>

void	ft_printstack(t_stack *a)
{
	if (!a)
		printf("%p\n", a);
	while (a)
	{
		printf("%p<-[%zu]->%p\n", a->prev, a->num, a->next);
		a = a->next;
	}
	printf("\n");
}

void	opt_swap(t_stack **a)
{
	(void)a;
}

void	push_b_nonlisr(t_stack **a, t_stack **b)
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
		{
			p(a, b, "pb");
			opt_swap(b);
		}
		else
			r(a, b, "ra");
	}
}

void	push_b_nonlisrr(t_stack **a, t_stack **b)
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
		{
			p(a, b, "pb");
			opt_swap(b);
		}
		else
			rr(a, b, "rra");
	}
}

void	push_b_nonlis(t_stack **a, t_stack **b)
{
	t_stack *tmp;
	ssize_t	max_dr;
	ssize_t	max_drr;

	max_dr = -1;
	max_drr = -1;
	tmp = *a;
	while (tmp)
	{
		if (tmp->lis == 1)
		{
			if (max_drr == -1)
				max_drr = tmp->d_down;
			if (max_dr < tmp->d_up)
				max_dr = tmp->d_up;
		}
		tmp = tmp->next;
	}
	if (max_dr > max_drr)
		push_b_nonlisrr(a, b);
	else
		push_b_nonlisr(a, b);
}

void	set_d(t_stack *a, t_stack *b)
{
	ssize_t	i;

	i = 0;
	while (a || b)
	{
		if (a)
		{
			a->d_up = i;
			a->d_down = ft_stacksize(a) - i;
			a = a->next;
		}
		if (b)
		{
			b->d_up = i;
			b->d_down = ft_stacksize(b) - i;
			b = b->next;
		}
		i++;
	}
}

ssize_t	min(t_stack *a)
{
	ssize_t i;

	i = -1;
	while (a)
	{
		if (i == -1 || i > a->num)
			i = a->num;
		a = a->next;
	}
	return (i);
}

ssize_t	max(t_stack *a)
{
	ssize_t i;

	i = -1;
	while (a)
	{
		if (i == -1 || i < a->num)
			i = a->num;
		a = a->next;
	}
	return (i);
}

t_stack	*find_opt(t_stack *a, t_stack *b)
{
	t_stack	*tmp;

	tmp = a;
	if ((b->num > ft_stacklast(a)->num && b->num < a->num) || (b->num < min(a) && a->num == min(a)))
		return (a);
	while (a && a->next)
	{
		if (b->num < a->next->num && ((a->num == max(tmp) && a->next->num == min(tmp)) || (b->num > a->num)))
			break ;
		a = a->next;
	}
	return (a->next);
}

void	set_moves(t_stack *b, t_stack *opt)
{
	ssize_t	min;

	b->d_uu = ((b->d_up >= opt->d_up) * b->d_up +
		(b->d_up < opt->d_up) * opt->d_up);
	min = b->d_uu;
	b->d_dd = ((b->d_down >= opt->d_down) * b->d_down +
		(b->d_down < opt->d_down) * opt->d_down);
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
	num	= -1;
	tmp = b;
	while (b)
	{
		opt = find_opt(a, b);
		set_moves(b, opt);
		if (num == -1 || min > b->d_opt)
		{
			num = b->num;
			min = b->d_opt;
		}
		b = b->next;
	}
	while (tmp)
	{
		tmp->opt = (num == tmp->num) * min;
		tmp = tmp->next;
	}
}

ssize_t	find_case(t_stack *b)
{
	while (b)
	{
		if (b->opt)
			break;
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

void	uu(t_stack **a, t_stack **b)
{
	t_stack	*opt_a;
	t_stack	*opt_b;
	ssize_t	i;

	i = -1;
	opt_b = *b;
	while (opt_b)
	{
		if (opt_b->opt)
			break ;
		opt_b = opt_b->next;
	}
	opt_a = find_opt(*a, opt_b);
	while (++i < (opt_a->d_up * (opt_a->d_up <= opt_b->d_up) +
		opt_b->d_up * (opt_a->d_up > opt_b->d_up)))
		r(a, b, "rr");
	while (i < opt_a->d_up && ++i > -1)
		r(a, b, "ra");
	while (i < opt_b->d_up && ++i > -1)
		r(a, b, "rb");
}

void	dd(t_stack **a, t_stack **b)
{
	t_stack	*opt_a;
	t_stack	*opt_b;
	ssize_t	i;

	i = -1;
	opt_b = *b;
	while (opt_b)
	{
		if (opt_b->opt)
			break ;
		opt_b = opt_b->next;
	}
	opt_a = find_opt(*a, opt_b);
	while (++i < (opt_a->d_down * (opt_a->d_down <= opt_b->d_down) +
		opt_b->d_down * (opt_a->d_down > opt_b->d_down)))
		rr(a, b, "rrr");
	while (i < opt_a->d_down && ++i > -1)
		rr(a, b, "rra");
	while (i < opt_b->d_down && ++i > -1)
		rr(a, b, "rrb");
}

void	ud(t_stack **a, t_stack **b)
{
	t_stack	*opt_a;
	t_stack	*opt_b;
	ssize_t	i;

	i = -1;
	opt_b = *b;
	while (opt_b)
	{
		if (opt_b->opt)
			break ;
		opt_b = opt_b->next;
	}
	opt_a = find_opt(*a, opt_b);
	while (++i < opt_a->d_up)
		r(a, b, "ra");
	i = -1;
	while (++i < opt_b->d_down)
		rr(a, b, "rrb");
}

void	du(t_stack **a, t_stack **b)
{
	t_stack	*opt_a;
	t_stack	*opt_b;
	ssize_t	i;

	i = -1;
	opt_b = *b;
	while (opt_b)
	{
		if (opt_b->opt)
			break ;
		opt_b = opt_b->next;
	}
	opt_a = find_opt(*a, opt_b);
	while (++i < opt_a->d_up)
		r(a, b, "rb");
	i = -1;
	while (++i < opt_b->d_down)
		rr(a, b, "rra");
}

void	turn_till_opt(t_stack **a, t_stack **b, ssize_t c)
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

/*void	push_opt(t_stack **a, t_stack **b)
{
}*/

ssize_t	is_sorted(t_stack *a)
{
	while (a && a->next)
	{
		if (a->num > a->next->num)
			return (0);
		a = a->next;
	}
	return (1);
}

void	push_swap(t_stack **a, t_stack **b, ssize_t size)
{
	ssize_t pushed;
	ssize_t	c;
	
	pushed = 0;
	c = 0;
	while ((!is_sorted(*a) && pushed == 0) || size != ft_stacksize(*a))
	{
		set_d(*a, *b);
		if(pushed == 0)
		{
			push_b_nonlis(a, b);
			pushed = 1;
			continue ;
		}
		//printf("%zu\n", c);
		//ft_printstack(*a);
		//ft_printstack(*b);
		set_opt(*a, *b);
		c = find_case(*b);
		turn_till_opt(a, b, c);
		p(a, b, "pa");
	}
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
	push_swap(&a, &b, ps.size);
	ft_stackclear(&a);
}