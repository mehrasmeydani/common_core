/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/18 15:53:52 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	t_uc	*tmp1;
	t_uc	*tmp2;

	if (!n || (!src && !dest))
		return (dest);
	tmp1 = (t_uc *)dest;
	tmp2 = (t_uc *)src;
	i = -1;
	while (++i < n)
		tmp1[i] = tmp2[i];
	return (dest);
}
