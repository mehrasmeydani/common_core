/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:56:42 by megardes          #+#    #+#             */
/*   Updated: 2025/05/18 18:11:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/pipex.h"

int main(void)
{
	pid_t	pid;
	int		status;
	char	*env[] = {NULL};
	char	*av[] = {"/usr/bin/ls", "-l", "-a", NULL};	
	char	*av2[] = {"/bin/grep", "srcs", NULL};
	char	*av3[] = {"/bin/awk", "{print $1, $2, $3}", NULL};

	int		fd[2] = {};
	pipe(fd);
	pid	= fork();
	if (pid == 0)
	{
		int		fd1[2] = {};
		pipe(fd1);
		pid = fork();
		if (pid == 0)
		{
			if (dup2(fd1[1], 1) == -1)
				return (ft_putstr_fd("what", 1), 1);
			close(fd1[0]);
			close(fd1[1]);
			close(fd[0]);
			close(fd[1]);
			execve(av[0], av, env);
		}
		else
		{
			waitpid(pid, &status, 0);
			dup2(fd1[0], 0);
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			close(fd1[0]);
			close(fd1[1]);
			execve(av2[0], av2, env);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execve(av3[0], av3, env);
	}
	write(1, "what", 4);
}