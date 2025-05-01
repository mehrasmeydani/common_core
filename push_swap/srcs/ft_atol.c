/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:17:43 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 12:18:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

long	ft_atol(const char *nptr)
{
	long	out;
	ssize_t	j;
	long	sign;

	out = 0;
	j = -1;
	sign = 1;
	while (nptr[++j] == 32 || (nptr[j] >= 9 && nptr[j] <= 13))
		;
	if ((nptr[j] == '-' || nptr[j] == '+') && ++j)
		if (nptr[j - 1] == '-')
			sign = -1;
	while (nptr[j] >= '0' && nptr[j] <= '9')
		out = out * 10 + nptr[j++] - '0';
	return (out * sign);
}
