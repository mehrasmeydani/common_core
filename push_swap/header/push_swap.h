/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:33 by codespace         #+#    #+#             */
/*   Updated: 2025/04/30 17:04:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../libft/libft.h"
# include <stdbool.h>

typedef struct s_push_swap
{
	char	***in;
	char	**out;
	long	*num;
	long	*sorted;
	ssize_t	*idx;
	ssize_t	*lis_util;
	ssize_t	*lis;
	ssize_t	*lis_util2;
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

void	init(t_ps *in, t_stack *a, t_stack *b);
char	***ft_splits(ssize_t argc, char **argv);
ssize_t	ft_strstrstrlen(char ***in);
ssize_t	ft_strstrlen(char **in);
char	**ft_free(char **in, ssize_t i);
char	***ft_free_free(char ***in, ssize_t i);

#endif