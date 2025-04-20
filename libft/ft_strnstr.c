/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/18 16:45:13 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = -1;
	if (!big && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	while (big[++i] && i < len)
	{
		j = -1;
		while (big[i + ++j] && big[i + j] == little[j] && i + j < len)
			if (!little[j + 1])
				return ((char *)(big + i));
	}
	return (NULL);
}
