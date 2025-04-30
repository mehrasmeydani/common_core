/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:00:08 by codespace         #+#    #+#             */
/*   Updated: 2025/04/30 16:05:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

char	***ft_splits(ssize_t argc, char **argv)
{
	char	***out;
	ssize_t	i;

	i = -1;
	out = (char ***)malloc((argc + 1) * sizeof(char **));
	if (!out)
		return (NULL);
	out[argc] = NULL;
	while (++i < argc)
	{
		out[i] = ft_split(argv[i], ' ');
		if (!out[i])
			return (ft_free_free(out, i));
	}
	return (out);
}
