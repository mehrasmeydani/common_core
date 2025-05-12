/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:31:02 by megardes          #+#    #+#             */
/*   Updated: 2025/05/12 18:41:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;

	if (!s || !len)
		return (NULL);
	if (start > ft_strlen(s) || len * ft_strlen(s) == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len + start > ft_strlen(s))
		out = (char *)ft_calloc((ft_strlen(s) - start + 1), sizeof(char));
	else
		out = (char *)ft_calloc((len + 1), sizeof(char));
	if (!out)
		return (NULL);
	if (len > ft_strlen(s))
		ft_strlcat(out, s + start, ft_strlen(s) + 1);
	else
		ft_strlcat(out, s + start, len + 1);
	return (out);
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
		return (free(in), NULL);
	ft_strlcat(out, in, ft_strlen(in) + 1);
	ft_strlcat(out, buff, ft_strlen(out) + mlen);
	free(in);
	return (out);
}

void	left(char *in, char left[BUFFER_SIZE + 1])
{
	char	*tmp;

	tmp = ft_strchr(in, '\n') + 1;
	left[0] = 0;
	ft_strlcat(left, tmp, ft_strlen(tmp) + 1);
	free(in);
}

char	*readfile(int fd, char *red)
{
	char		*buff;
	ssize_t		r;

	buff = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
		return (free(red), NULL);
	while (!red || !ft_strchr(red, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
			return (free(red), free(buff), NULL);
		if (r == 0)
			break ;
		buff[r] = 0;
		red = ft_relocat(red, buff);
		if (!red)
			return (free(buff), NULL);
	}
	free(buff);
	return (red);
}

char	*get_next_line(int fd)
{
	static char	red[FD_SIZE][BUFFER_SIZE + 1] = {};
	char		*out;
	char		*tmp;

	tmp = ft_substr(red[fd], 0, ft_strlen(red[fd]));
	out = NULL;
	if (fd < 0)
		return (NULL);
	tmp = readfile(fd, tmp);
	if (!tmp)
		return (red[fd][0] = 0, NULL);
	if (ft_strchr(tmp, '\n'))
	{
		out = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - tmp + 1);
		if (!out)
			return (red[fd][0] = 0, free(tmp), NULL);
		left(tmp, red);
		return (out);
	}
	return (red[fd][0] = 0, out = tmp, out);
}
