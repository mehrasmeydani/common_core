/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:21 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 11:33:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>

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
