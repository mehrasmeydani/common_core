/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_long_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:18:43 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 11:26:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

static void	ft_swap(long *a, long *b)
{
	long	why;

	why = *a;
	*a = *b;
	*b = why;
}

void	ft_sort_long_tab(long *tab, ssize_t size)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (++i < size)
	{
		j = i;
		while (++j < size)
			if (tab[j] < tab[i])
				ft_swap(&tab[j], &tab[i]);
	}
}
