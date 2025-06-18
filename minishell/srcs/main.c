/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:59:20 by megardes          #+#    #+#             */
/*   Updated: 2025/06/18 20:33:49 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_errno = 0;

void	minishell(void)
{
	char *line;

	while(1)
	{
		while(g_errno == 0)
		{
			line = readline("minishell>");
			printf("%s", line);
			if(line && !ft_strncmp("exit", line, 4))
				exit(1);
			free(line);
		}
		g_errno = 0;
	}
}

void	type_c(int signum, siginfo_t *info, void *str)
{
	(void)info;
	(void)str;
	(void)signum;
	ft_putendl_fd("^C", 2);
}

void	set_sig(void)
{
	struct sigaction sig;
	sig.sa_sigaction = &type_c;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigemptyset(&(sig.sa_mask)))
		return (ft_putendl_fd("sigemptyset failed", 2));
	sigaction(SIGINT, &sig, NULL);
	g_errno = 130;
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	set_sig();
	//set_env();
	minishell();
}