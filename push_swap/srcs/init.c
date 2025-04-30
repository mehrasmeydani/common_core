/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:58:21 by codespace         #+#    #+#             */
/*   Updated: 2025/04/30 17:04:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

void	init(t_ps *in, t_stack *a, t_stack *b)
{
	in->in = NULL;
	in->out = NULL;
	in->lis = NULL;
	in->num = NULL;
	in->sorted = NULL;
	in->lis_util = NULL;
	in->idx = NULL;
	in->size = 0;
	b->d_down = 0;
	b->d_opt = 0;
	b->d_up = 0;
	b->num = 0;
	b->next = NULL;
	b->prev = NULL;
	a->d_down = 0;
	a->d_opt = 0;
	a->d_up = 0;
	a->num = 0;
	a->next = NULL;
	a->prev = NULL;
}
