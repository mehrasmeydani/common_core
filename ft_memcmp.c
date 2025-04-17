/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/17 10:56:37 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	t_uc	*tmp1;
	t_uc	*tmp2;

	i = 0;
	tmp1 = (t_uc *)s1;
	tmp2 = (t_uc *)s2;
	while (tmp1[i] == tmp2[i] && i < n)
		i++;
	return (tmp1[i] - tmp2[i]);
}
