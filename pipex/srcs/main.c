/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:15:05 by megardes          #+#    #+#             */
/*   Updated: 2025/05/22 11:52:23 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

char	**set_env(void)
{
	char **out;

	out = ft_calloc(2, sizeof(char *));
	if (!out)
		return (NULL);
	out[0] = ft_strdup("PATH=.");
	if (!out)
		return (free(out), NULL);
	return (out);
}

t_pipex	*parse(int argc, char **argv)
{
	
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	*pipe;
	ssize_t	i;

	if (argc < 5)
		return (ft_putstr_fd("invalid input", 2), 1);
	i = -1;
	if (!env[0])
		env = set_env();
	pipe = parse(argc, argv);
	pipex(pipe);
}