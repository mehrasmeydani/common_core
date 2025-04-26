/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:31:02 by megardes          #+#    #+#             */
/*   Updated: 2025/04/26 15:29:20 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
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
	char *out;
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE];
	static char *red = NULL;
	ssize_t		r;

	if (fd < 0)
		return (NULL);
	while (!red || !ft_strchr(red, '\n'))
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
			return (free(red), red = NULL, NULL);
		if (r == 0)
			break;
		red = ft_relocat(red, buff);
	}
}