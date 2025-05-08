/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:00:08 by codespace         #+#    #+#             */
/*   Updated: 2025/05/08 07:51:29 by megardes         ###   ########.fr       */
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
		if (!argv[i][0])
			return (ft_putendl_fd("Error", 2), ft_free_free(out, i));
		out[i] = ft_split(argv[i], ' ');
		if (!out[i] || !out[i][0])
			return (ft_free_free(out, i));
	}
	return (out);
}
