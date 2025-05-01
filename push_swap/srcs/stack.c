/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:04:10 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 12:22:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

t_stack	*ft_stacknew(t_ps *in, ssize_t i)
{
	t_stack	*new;

	new = (t_stack *)ft_calloc(sizeof(t_stack), 1);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->lis = in->lis[i];
	new->num = in->idx[i];
	return (new);
}

t_stack	*ft_stacklast(t_stack *stack)
{
	while (stack && stack->next)
		stack = stack->next;
	return (stack);
}

t_stack	*ft_stackfirs(t_stack *stack)
{
	while (stack && stack->prev)
		stack = stack->prev;
	return (stack);
}

void	ft_stackadd_back(t_stack **stack, t_stack *new)
{
	t_stack	*tmp;

	if (stack)
	{
		tmp = ft_stacklast(*stack);
		if (tmp)
			(tmp)->next = new;
		else
			*stack = new;
	}
}

void	ft_stackclear(t_stack **stack)
{
	t_stack	*tmp;

	if (stack)
	{
		while (*stack)
		{
			tmp = *stack;
			*stack = (*stack)->next;
			free(tmp);
		}
	}
}
