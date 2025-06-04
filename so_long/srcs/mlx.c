/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:22:19 by megardes          #+#    #+#             */
/*   Updated: 2025/06/04 14:34:03 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	my_put_img(t_mlx *mlx, t_map *map, ssize_t x, ssize_t y)
{
	if (map->map[y][x] == 'P')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->player_status,
			x * XPM_SIZE, y * XPM_SIZE);
	if (map->map[y][x] == 'E')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->exit_status,
			x * XPM_SIZE, y * XPM_SIZE);
	if (map->map[y][x] == 'C')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->collect,
			x * XPM_SIZE, y * XPM_SIZE);
	if (map->map[y][x] == '0')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->empty,
			x * XPM_SIZE, y * XPM_SIZE);
	if (map->map[y][x] == '1')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->wall,
			x * XPM_SIZE, y * XPM_SIZE);
}

void	set_window(t_mlx *mlx, t_map *map, char *num)
{
	ssize_t	y;
	ssize_t	x;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
			my_put_img(mlx, map, x, y);
	}
	mlx_string_put(mlx->mlx, mlx->win, 20, 20, 0xFF000000, num);
}

void	change_dir(t_img *img, ssize_t y, ssize_t x)
{
	if (x == -1)
		img->player_status = img->player_left;
	if (x == 1)
		img->player_status = img->player_right;
	if (y == -1)
		img->player_status = img->player_up;
	if (y == 1)
		img->player_status = img->player_down;
}

void	hook_all(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0, exit_mlx, mlx);
	mlx_hook(mlx->win, 2, (1L << 0), key, mlx);
}

void	init_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		error_and_exit("MLX was not initiated!", 2, mlx->map);
	mlx->win = mlx_new_window(mlx->mlx, XPM_SIZE * mlx->map->x,
			XPM_SIZE * mlx->map->y, "so_long");
	if (!mlx->win)
		error_and_exit_mlx("WIN was not initiated", 2, mlx);
	init_img(mlx, mlx->img, 0, 0);
	set_window(mlx, mlx->map, "0");
	hook_all(mlx);
	mlx_loop(mlx->mlx);
}
