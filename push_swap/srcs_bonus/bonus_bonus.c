/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 05:32:12 by megardes          #+#    #+#             */
/*   Updated: 2025/05/08 11:53:43 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/bonus_bonus.h"

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
	if (!a)
		return (1);
	b = NULL;
	checker(&a, &b, ps.size);
}
