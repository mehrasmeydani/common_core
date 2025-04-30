/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:01:07 by codespace         #+#    #+#             */
/*   Updated: 2025/04/30 16:04:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

ssize_t	ft_strstrstrlen(char ***in)
{
	ssize_t	i;

	i = -1;
	if (!in)
		return (0);
	while (in[++i])
		;
	return (i);
}

ssize_t	ft_strstrlen(char **in)
{
	ssize_t	i;

	i = -1;
	if (!in)
		return (0);
	while (in[++i])
		;
	return (i);
}

char	**ft_free(char **in, ssize_t i)
{
	ssize_t	j;

	j = -1;
	while (++j < i)
		free(in[j]);
	free(in);
	return (NULL);
}

char	***ft_free_free(char ***in, ssize_t i)
{
	ssize_t	j;

	j = -1;
	while (++j < i)
		ft_free(in[j], ft_strstrlen(in[j]));
	free(in);
	return (NULL);
}
