/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:41 by megardes          #+#    #+#             */
/*   Updated: 2025/05/28 22:00:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <X11/keysym.h>

# ifndef XPM_SIZE
#  define XPM_SIZE 32
# endif

# ifndef X
#  define X 1
# endif

# ifndef Y
#  define Y 0
# endif

typedef struct s_map
{
	ssize_t	x;
	ssize_t	y;
	ssize_t	x_first;
	ssize_t	player;
	ssize_t	exit;
	ssize_t	collect;
	ssize_t	bytes_read;
	ssize_t	i;
	ssize_t	e[2];
	ssize_t	p[2];
	int		fd;
	char	**map;
	char	**map_copy;
	char	r[2];
}	t_map;

typedef struct s_img
{
	void	*player;
	void	*collect;
	void	*empty;
	void	*wall;
	void	*exit;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_map	*map;
}	t_mlx;

#endif