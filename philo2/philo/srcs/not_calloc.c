/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:06:14 by megardes          #+#    #+#             */
/*   Updated: 2025/07/28 16:52:16 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mylib.h"

void	*not_calloc(size_t nmemb, size_t size)
{
	void	*out;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if ((size * nmemb) / nmemb != size)
		return (NULL);
	out = (void *)malloc(nmemb * size);
	if (!out)
		return (NULL);
	not_bzero(out, nmemb * size);
	return (out);
}
