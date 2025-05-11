/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:41 by megardes          #+#    #+#             */
/*   Updated: 2025/05/11 20:59:21 by megardes         ###   ########.fr       */
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
	ssize_t	p;
	ssize_t	e;
	ssize_t c;
	ssize_t	bytes_read;
	char	**map;
	char	**map_copy;
	char	r[2];
}	t_map;

typedef struct s_mlx
{
	t_map	*map;
}	t_mlx;



#endif