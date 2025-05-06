/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:31:23 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 11:31:48 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

ssize_t	min(t_stack *a)
{
	ssize_t	i;

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
	ssize_t	i;

	i = -1;
	while (a)
	{
		if (i == -1 || i < a->num)
			i = a->num;
		a = a->next;
	}
	return (i);
}
