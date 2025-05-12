/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:31:02 by megardes          #+#    #+#             */
/*   Updated: 2025/05/12 17:22:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		return (free(in), NULL);
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
	free(in);
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

char	*readfile(int fd, char *red)
{
	char		*buff;
	ssize_t		r;

	buff = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (free(red), red = NULL);
	while (!red || !ft_strchr(red, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
			return (free(buff), free(red), red = NULL);
		if (r == 0)
			break ;
		buff[r] = 0;
		red = ft_relocat(red, buff);
		if (!red)
			return (free(buff), red = NULL);
	}
	free(buff);
	return (red);
}

char	*get_next_line(int fd)
{
	static char	*red[2048] = {};
	char		*out;

	if (fd < 0)
		return (NULL);
	red[fd] = readfile(fd, red[fd]);
	if (!red[fd])
		return (NULL);
	if (ft_strchr(red[fd], '\n') && *(ft_strchr(red[fd], '\n') + 1))
	{
		out = clean(red[fd]);
		if (!out)
			return (free(red[fd]), red[fd] = NULL);
		red[fd] = left(red[fd]);
		if (!red[fd])
			return (free(out), red[fd] = NULL);
		return (out);
	}
	return (out = red[fd], red[fd] = NULL, out);
}
