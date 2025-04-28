/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:33 by codespace         #+#    #+#             */
/*   Updated: 2025/04/28 19:07:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdbool.h>

typedef	struct s_push_swap
{
	char	***in;
	char	**out;
	long	*num;
	long	*sorted;
	bool	*lis;
	ssize_t	size;
}	t_ps;

typedef struct s_stack
{
	int					num;
	int					d_up;
	int					d_down;
	int					d_opt;
	int					lis;
	bool				opt;
	struct s_push_swap	*next;
	struct s_push_swap	*prev;	
}	t_stack;

#endif