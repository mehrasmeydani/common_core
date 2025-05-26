/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:56:42 by megardes          #+#    #+#             */
/*   Updated: 2025/05/22 13:23:00 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/pipex.h"
#include <stdio.h>

void	ft_pipclear(t_pipex **lst)
{
	t_pipex	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = *lst;
			*lst = (*lst)->next;
			free(tmp);
		}
	}
}

t_pipex	*ft_pipnew(void *content)
{
	t_pipex	*out;

	out = (t_pipex *)ft_calloc(sizeof(t_pipex), 1);
	if (!out)
		return (NULL);
	out->argv = content;
	return (out);
}

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	//pid_t	pid2;
	int		status;
	int		fd = open("test.c", O_RDONLY);
	int		fd2 = open("lol.txt", 00777,  O_RDWR);
	char	*av[] = {"/bin/cat",  NULL};	
	char	*av2[] = {"/bin/grep", "srcs", NULL};
	char	*av3[] = {"/bin/awk", "{print $1, $2, $3}", NULL};
	t_pipex	*test;
	t_pipex	*tmp;
	(void)argc;
	(void)argv;

	test = ft_pipnew(av);
	test->next = ft_pipnew(av2);
	test->next->next = ft_pipnew(av3);
	test->next->prev = test;
	test->next->next->prev = test->next;
	tmp = test;
	(void)tmp;
	while (test)
	{
		pipe(test->fd);
		pid = fork();
		if (pid == 0)
		{
			if (test->prev)
			{
				dup2(test->prev->fd[0], 0);
				close(test->prev->fd[0]);
			}
			else
				dup2(fd, 0);
			if (test->next)
				dup2(test->fd[1], 1);
			else
				dup2(fd2, 1);
			close(test->fd[0]);
			close(test->fd[1]);
			execve(test->argv[0], test->argv, env);
			ft_pipclear(&tmp);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			// if (status != 0)
			// 	error_n_exit(2, "", &tmp);
			if (test->prev)
				close(test->prev->fd[0]);
			close(test->fd[1]);
			if (!test->next)
				close(test->fd[0]);
			test = test->next;
		}
	}
	ft_pipclear(&tmp);
	write(1, "what", 4);
}