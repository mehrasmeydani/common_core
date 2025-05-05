/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nums.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:21:13 by codespace         #+#    #+#             */
/*   Updated: 2025/05/05 20:24:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"

void	ft_nums(t_ps *in)
{
	ssize_t	i[3];

	i[0] = 0;
	i[1] = -1;
	if (!in || !in->in)
		return ;
	while (in->in[++(i[1])])
		i[0] += ft_strstrlen(in->in[i[1]]);
	in->out = (char **)ft_calloc((i[0] + 1), sizeof(char *));
	if (!in->out)
		return ;
	i[2] = -1;
	i[1] = -1;
	while (in->in[++i[1]])
	{
		i[0] = -1;
		while (in->in[i[1]][++i[0]] && ++i[2] > -1)
			in->out[i[2]] = in->in[i[1]][i[0]];
		free(in->in[i[1]]);
	}
	free(in->in);
	in->size = i[2] + 1;
}
