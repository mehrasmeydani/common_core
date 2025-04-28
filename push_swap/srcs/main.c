/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:43:21 by codespace         #+#    #+#             */
/*   Updated: 2025/04/28 19:40:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/push_swap.h"
#include <stdio.h>

long	ft_atol(const char *nptr)
{
	long		out;
	ssize_t	j;
	long		sign;

	out = 0;
	j = -1;
	sign = 1;
	while (nptr[++j] == 32 || (nptr[j] >= 9 && nptr[j] <= 13))
		;
	if ((nptr[j] == '-' || nptr[j] == '+') && ++j)
		if (nptr[j - 1] == '-')
			sign = -1;
	while (nptr[j] >= '0' && nptr[j] <= '9')
		out = out * 10 + nptr[j++] - '0';
	return (out * sign);
}

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

char	***ft_splits(ssize_t argc, char **argv)
{
	char	***out;
	ssize_t	i;

	i = -1;
	out = (char ***)malloc((argc + 1) * sizeof(char **));
	if (!out)
		return (NULL);
	out[argc] = NULL;
	while(++i < argc)
	{
		out[i] = ft_split(argv[i], ' ');
		if (!out[i])
			return (ft_free_free(out, i));
	}
	return (out);
}

void	ft_nums(t_ps *in)
{
	ssize_t	i[3];

	i[0] = 0;
	i[1] = -1;
	if (!in || !in->in)
		return ;
	while (in->in[++(i[1])])
		i[0] += ft_strstrlen(in->in[i[1]]);
	in->out = (char	**)malloc((i[0] + 1) * sizeof(char *));
	if (!in->out)
		return ;
	in->out[i[0]] = NULL;
	i[2] = -1;
	i[1] = -1;
	while (in->in[++i[1]])
	{
		i[0] = -1;
		while (in->in[i[1]][++i[0]] && ++i[2] > -1)
			in->out[i[2]] = in->in[i[1]][i[0]];
		free(in->in[i[1]]);
		in->in[i[1]] = NULL;
	}
	free(in->in);
	in->in = NULL;
	in->size = i[2];
}

void	init(t_ps *in, t_stack *a, t_stack *b)
{
	in->in = NULL;
	in->out = NULL;
	in->lis = NULL;
	in->num = NULL;
	in->sorted = NULL;
	in->size = 0;
	b->d_down = 0;
	b->d_opt = 0;
	b->d_up = 0;
	b->num = 0;
	b->next = NULL;
	b->prev = NULL;
	a->d_down = 0;
	a->d_opt = 0;
	a->d_up = 0;
	a->num = 0;
	a->next = NULL;
	a->prev = NULL;
}

bool	valid(char *in)
{
	int		sign;
	ssize_t	i;
	
	i = -1;
	sign = 0;
	while (in[++i])
	{
		if (!ft_isdigit(in[i]) && !(in[i] == '-' || in[i] == '+'))
			return (0);
		if (in[i] == '-' || in[i] == '+')	
			sign++;
		if (sign > 1)
			return (0);
	}
	return (1);
}

void	tol(t_ps *in)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	in->num = (long *)malloc(sizeof(long) * in->size);
	if (!in->num)
		return ;
	while (++i < in->size)
	{
		j = -1;
		in->num[i] = ft_atol(in->out[i]);
		while (++j < i)
			if (in->num[j] == in->num[i] || in->num[i] > 2147483647
				|| in->num[i] < -2147483648 || !valid(in->out[i]))
				return (free(in->num), (void)(in->num = NULL), 
						ft_putendl_fd("Error", 2));
	}
}

bool	check(t_ps *in, t_stack *a, t_stack *b)
{
	tol(in);
	ft_free(in->out, ft_strstrlen(in->out));
	if (!in->num)
		return (0);
	(void)a;
	(void)b;
	return (1);
}

int	main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	a;
	t_stack b;

	if (argc < 2)
		return (1);
	init(&ps, &a, &b);
	ps.in = ft_splits((ssize_t)(argc - 1), &argv[1]);
	ft_nums(&ps);
	if (!ps.out)
		return (puts("what"), ft_free_free(ps.in, ft_strstrstrlen(ps.in)), 1);
	if (!check(&ps, &a, &b))
	 	return (1);
	//ft_free_free(ps.in, ft_strstrstrlen(ps.in));
	free(ps.num);
	//push_swap(&ps, &a, &b);
}
