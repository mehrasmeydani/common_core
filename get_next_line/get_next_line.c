/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:31:02 by megardes          #+#    #+#             */
/*   Updated: 2025/04/26 17:33:51 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

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

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (tmp = (char *)(s + i), tmp);
	if (s[i] == (char)c)
		return (tmp = (char *)(s + i), tmp);
	return (NULL);
}

char	*ft_relocat(char *in, char buff[BUFFER_SIZE])
{
	char	*out;
	size_t	mlen;

	mlen = ft_strlen(buff) + 1;
	if (!in)
	{
		out = (char *)ft_calloc(mlen, 1);
		if (!out)
			return (NULL);
		ft_strlcat(out, buff, mlen);
		return (out);
	}
	out = (char *)ft_calloc(ft_strlen(in) + mlen, 1);
	if (!out)
		return (NULL);
	ft_strlcat(out, in, ft_strlen(in) + 1);
	ft_strlcat(out, buff, ft_strlen(out) + mlen);
	free(in);
	return (out);
}

char	*left(char *in)
{
	char	*out;
	char	*tmp;

	tmp = ft_strchr(in, '\n') + 1;
	out = (char *)ft_calloc(ft_strlen(tmp) + 1, 1);
	if (!out)
		return (free(in), NULL);
	ft_strlcat(out, tmp, ft_strlen(tmp) + 1);
	*(ft_strchr(in, '\n') + 1) = 0;
	return (out);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE];
	static char	*red = NULL;
	char		*out;
	ssize_t		r;

	out = red;
	if (fd < 0)
		return (NULL);
	while (!out || !ft_strchr(out, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
			return (free(out), out = NULL, free(red), red = NULL, NULL);
		if (r == 0)
			break ;
		out = ft_relocat(out, buff);
		if (!out)
			return (free(out), out = NULL, free(red), red = NULL, NULL);
	}
	if (ft_strchr(out, '\n'))
	{
		red = left(out);
		return (out);
	}
	return (red = NULL, out);
}
