/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:15:28 by megardes          #+#    #+#             */
/*   Updated: 2025/05/22 11:52:08 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <wait.h>

typedef struct s_pipex
{
	char	**argv;
	int		fd[2];
	int		fd_in;
	int		fd_out;
	struct s_pipex	*next;
	struct s_pipex	*prev;
}	t_pipex;

#endif