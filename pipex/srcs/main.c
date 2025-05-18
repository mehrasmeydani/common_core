/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:15:05 by megardes          #+#    #+#             */
/*   Updated: 2025/05/18 15:53:53 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int argc, char **argv)
{
	int		tmp_fd;
	pid_t	pid;

	tmp_fd = open("tmp.txt", O_CREAT, O_RDWR);
	pid = fork();
	if (pid < 0)
		return (close(tmp_fd), ft_putendl_fd("what", 2), 1);
	if (pid == 0)
	{
		if (dup2(tmp_fd, STDOUT_FILENO) != -1)
			execve("ls", NULL, NULL);
	}
	else
	{
		wait(NULL);
		
	}
}