/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/23 12:13:36 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(const char *str, char c)
{
	int		j;
	int		i;

	j = 0;
	i = 0;
	while (str[j])
	{
		while (str[j] && (str[j] == c))
			j++;
		if (str[j] && !(str[j] == c))
			i++;
		while (str[j] && !(str[j] == c))
			j++;
	}
	return (i);
}

char	**ft_free(char **in, int i)
{
	int	j;

	j = -1;
	while (++j < i)
		free(in[j]);
	free(in);
	return (NULL);
}

char	*str(char *s, char c)
{
	int		i;
	char	*out;

	i = -1;
	while (s[++i] && s[i] != c)
		;
	out = ft_substr(s, 0, i);
	if (!out)
		return (NULL);
	return (out);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	char	*tmp;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	out = (char **)malloc((count(s, c) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	tmp = (char *)s;
	while (++i < count(s, c))
	{
		while (*tmp && *tmp == c)
			tmp++;
		out[i] = str(tmp, c);
		if (!out[i])
			return (ft_free(out, i));
		while (*tmp && *tmp != c)
			tmp++;
	}
	out[i] = NULL;
	return (out);
}
