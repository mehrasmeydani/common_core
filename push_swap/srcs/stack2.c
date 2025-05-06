/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:15:05 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 11:27:04 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

void	ft_stackadd_front(t_stack **stack, t_stack *new)
{
	if (stack)
	{
		if (*stack)
			new->next = *stack;
		*stack = new;
	}
}

t_stack	*make_stack(t_ps *in)
{
	t_stack	*new;
	t_stack	*out;
	ssize_t	i;

	i = -1;
	out = NULL;
	while (++i < in->size)
	{
		new = ft_stacknew(in, i);
		if (!new)
			return (ft_stackclear(&out), NULL);
		ft_stackadd_back(&out, new);
	}
	return (out);
}

ssize_t	ft_stacksize(t_stack *in)
{
	ssize_t	i;

	i = 0;
	in = ft_stackfirst(in);
	while (in && ++i)
		in = in->next;
	return (i);
}
