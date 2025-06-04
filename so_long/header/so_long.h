/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:41 by megardes          #+#    #+#             */
/*   Updated: 2025/06/04 13:41:06 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include <mlx.h>
# include <string.h>
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
	void	*player_up;
	void	*player_down;
	void	*player_right;
	void	*player_left;
	void	*player_status;
	void	*enemy;
	void	*o_exit;
	void	*collect;
	void	*empty;
	void	*wall;
	void	*exit;
	void	*exit_status;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_map	*map;
}	t_mlx;

void	init_img(t_mlx *mlx, t_img *img, int img_width, int img_height);
void	read_map(t_map *map, char *str);
void	flood_worked(t_map *map);
void	find_player(t_map *map, ssize_t *y, ssize_t *x, char c);
void	flood_fill(t_map *map, ssize_t x, ssize_t y);
int		exit_mlx(t_mlx *mlx);
void	error_and_exit_mlx(char *error, int fd, t_mlx *mlx);
void	error_and_exit(char *error, int fd, t_map *map);
int		key(int keycode, t_mlx *mlx);
void	init_window(t_mlx *mlx);
void	set_window(t_mlx *mlx, t_map *map, char *num);
void	change_dir(t_img *img, ssize_t y, ssize_t x);
void	move(t_mlx *mlx, ssize_t y, ssize_t x);

#endif