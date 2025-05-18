/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:15:28 by megardes          #+#    #+#             */
/*   Updated: 2025/05/18 18:07:37 by codespace        ###   ########.fr       */
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
	struct s_pipex	*next;
	struct s_pipex	*prev;
}	t_pipex;

#endif