/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:15:16 by codespace         #+#    #+#             */
/*   Updated: 2025/05/12 17:20:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;
	char	*tmp;
	size_t	i;

	i = 0;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (nmemb == SIZE_MAX || size == SIZE_MAX
		|| (size * nmemb) / nmemb != size || size * nmemb > INT32_MAX)
		return (NULL);
	out = (void *)malloc(nmemb * size);
	if (!out)
		return (NULL);
	tmp = (char *)out;
	while (i < size)
	{
		tmp[i] = 0;
		i++;
	}
	return (out);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	dst_len;
	size_t	i;

	if ((dsize == 0 && !dst) || dsize <= ft_strlen(dst))
		return (ft_strlen(src) + dsize);
	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && ((i + dst_len) < dsize - 1))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (ft_strlen(src) + dst_len);
}

char	*ft_strchr(const char *s, int c)
{
	ssize_t	i;
	char	*tmp;

	if (!s)
		return (NULL);
	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (tmp = (char *)(s + i), tmp);
	if (s[i] == (char)c)
		return (tmp = (char *)(s + i), tmp);
	return (NULL);
}
