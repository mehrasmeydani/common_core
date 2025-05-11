/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:33 by codespace         #+#    #+#             */
/*   Updated: 2025/05/11 18:59:11 by megardes         ###   ########.fr       */
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
	ssize_t			num;
	ssize_t			d_up;
	ssize_t			d_down;
	ssize_t			d_opt;
	ssize_t			d_uu;
	ssize_t			d_dd;
	ssize_t			d_du;
	ssize_t			d_ud;
	bool			lis;
	ssize_t			opt;
	struct s_stack	*next;
	struct s_stack	*prev;	
	struct s_stack	*opt_node;
}	t_stack;

long	ft_atol(const char *nptr);
void	init(t_ps *in);
char	***ft_splits(ssize_t argc, char **argv);
ssize_t	ft_strstrstrlen(char ***in);
ssize_t	ft_strstrlen(char **in);
char	**ft_free(char **in, ssize_t i);
char	***ft_free_free(char ***in, ssize_t i);
void	set_lis(t_ps *in);
void	ft_sort_long_tab(long *tab, ssize_t size);
bool	check(t_ps *in);
void	ft_nums(t_ps *in);

void	ft_stackadd_front(t_stack **stack, t_stack *new);
t_stack	*ft_stacknew(t_ps *in, ssize_t i);
t_stack	*ft_stacklast(t_stack *stack);
t_stack	*ft_stackfirst(t_stack *stack);
void	ft_stackadd_back(t_stack **stack, t_stack *new);
void	ft_stackclear(t_stack **stack);
t_stack	*make_stack(t_ps *in);
ssize_t	ft_stacksize(t_stack *in);

void	s(t_stack **a, t_stack **b, char *c);
void	p(t_stack **a, t_stack **b, char *c);
void	r(t_stack **a, t_stack **b, char *c);
void	rr(t_stack **a, t_stack **b, char *c);

void	du(t_stack **a, t_stack **b);
void	ud(t_stack **a, t_stack **b);
void	dd(t_stack **a, t_stack **b);
void	uu(t_stack **a, t_stack **b);

void	set_opt(t_stack *a, t_stack *b);
t_stack	*find_opt(t_stack *a, t_stack *b);

ssize_t	max(t_stack *a);
ssize_t	min(t_stack *a);

void	push_swap(t_stack **a, t_stack **b, ssize_t size);
void	push_b_nonlis(t_stack **a, t_stack **b);
void	set_d(t_stack *a, t_stack *b);
ssize_t	is_sorted(t_stack *a);
void	sort_3(t_stack **a);

#endif