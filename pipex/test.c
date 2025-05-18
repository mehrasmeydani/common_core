/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:56:42 by megardes          #+#    #+#             */
/*   Updated: 2025/05/18 16:12:07 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/pipex.h"

int main(int argc, char **argv)
{
	pid_t	pid;
	int		fd[2];
	if (argc < 2)
		return (1);
	char *av[] = {"PATH=/bin", NULL};
	execve(argv[1], &argv[1], av);
	write(1, "what", 4);
}