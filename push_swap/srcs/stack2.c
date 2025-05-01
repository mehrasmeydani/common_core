/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:15:05 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 12:15:28 by codespace        ###   ########.fr       */
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
