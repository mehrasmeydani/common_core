/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:31:02 by megardes          #+#    #+#             */
/*   Updated: 2025/04/26 19:39:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char *red, char *buff, char *out)
{
	if (out)
	{
		free(out);
		out = NULL;
	}
	if (red)
	{
		free(red);
		red = NULL;
	}
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	return (buff);
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

char	*ft_relocat(char *in, char *buff)
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
		return (ft_free(in, NULL, NULL), NULL);
	ft_strlcat(out, in, ft_strlen(in) + 1);
	ft_strlcat(out, buff, ft_strlen(out) + mlen);
	ft_free(in, NULL, NULL);
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
	ft_free(in, NULL, NULL);
	return (out);
}

char	*clean(char *in)
{
	char	*out;

	out = (char *)ft_calloc(ft_strchr(in, '\n') - in + 2, 1);
	if (!out)
		return (NULL);
	ft_strlcat(out, in, ft_strchr(in, '\n') - in + 2);
	return (out);
}

char	*get_next_line(int fd)
{
	char		*buff;
	static char	*red = NULL;
	char		*out;
	ssize_t		r;

	if (fd < 0)
		return (NULL);
	buff = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (ft_free(red, NULL, NULL), red = NULL, NULL);
	while (!red || !ft_strchr(red, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
			return (ft_free(buff, red, NULL), red = NULL, NULL);
		if (r == 0)
			break ;
		buff[r] = 0;
		red = ft_relocat(red, buff);
		if (!red)
			return (ft_free(buff, NULL, NULL), red = NULL, NULL);
	}
	if (ft_strchr(red, '\n') && *(ft_strchr(red, '\n') + 1))
	{
		out = clean(red);
		if (!out)
			return (ft_free(red, buff, NULL), red = NULL, NULL);
		red = left(red);
		if (!red)
			return (red = NULL, ft_free(buff, NULL, NULL));
		return (ft_free(buff, NULL, NULL), out);
	}
	return (ft_free(buff, NULL, NULL),out = red, red = NULL, out);
}
