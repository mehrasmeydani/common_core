/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:21 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 15:14:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>

void	ft_printstack(t_stack *a)
{
	while (a)
	{
		printf("%p<-[%p]->%p\n", a->prev, a, a->next);
		a = a->next;
	}
}

void	push_swap(t_stack **a, t_stack **b)
{
	r(a, b, "ra");
	ft_printstack(*a);
	ft_putendl_fd("############\n", 1);
	rr(a, b, "rra");
	ft_printstack(*a);
	ft_putendl_fd("############\n", 1);
	p(a, b, "pb");
	ft_printstack(*a);
	ft_putendl_fd("############\n", 1);
	ft_printstack(*b);
	ft_putendl_fd("############\n", 1);
	p(a, b, "pa");
	ft_printstack(*a);
	ft_putendl_fd("############\n", 1);
	rr(a, b, "rra");
	ft_printstack(*a);
	ft_putendl_fd("############\n", 1);
	s(a, b, "sa");
	ft_printstack(*a);
	ft_putendl_fd("############\n", 1);
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
	push_swap(&a, &b);
	ft_stackclear(&a);
}