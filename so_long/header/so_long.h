/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:41 by megardes          #+#    #+#             */
/*   Updated: 2025/05/12 16:17:51 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <mlx.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_map
{
	ssize_t	x;
	ssize_t	y;
	ssize_t	x_first;
	ssize_t	player;
	ssize_t	exit;
	ssize_t collect;
	ssize_t	bytes_read;
	ssize_t	i;
	int		fd;
	char	**map;
	char	**map_copy;
	char	r[2];
}	t_map;

typedef struct s_mlx
{
	t_map	*map;
}	t_mlx;



#endif