/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:28:05 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 11:28:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

void	ft_printstack(t_stack *a, char c)
{
	printf("%c:\n", c);
	if (!a)
		printf("%p\n", a);
	while (a)
	{
		printf("%p<-[%zu]->%p\n", a->prev, a->num, a->next);
		a = a->next;
	}
	printf("\n");
}
