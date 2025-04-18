/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/18 12:52:18 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;

	if (nmemb == SIZE_MAX || size == SIZE_MAX || size * nmemb > sizeof(size_t))
		return (NULL);
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	out = (void *)malloc((nmemb * size));
	if (!out)
		return (NULL);
	ft_bzero(out, nmemb * size);
	return (out);
}
