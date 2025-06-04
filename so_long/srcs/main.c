/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:18 by megardes          #+#    #+#             */
/*   Updated: 2025/05/30 16:44:43 by megardes         ###   ########.fr       */
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

void	move(t_mlx *mlx, ssize_t y, ssize_t x)
{
	t_map			*map;
	char			*num;
	static ssize_t	move = 0;

	map = mlx->map;
	if (map->map[map->p[Y] + y][map->p[X] + x] == 'E' && map->collect == 0)
		error_and_exit_mlx("Come back soon", 1, mlx);
	if (map->map[map->p[Y] + y][map->p[X] + x] == '0'
		|| map->map[map->p[Y] + y][map->p[X] + x] == 'C')
	{
		if (map->map[map->p[Y] + y][map->p[X] + x] == 'C')
			map->collect--;
		if (map->collect == 0)
			mlx->img->exit_status = mlx->img->o_exit;
		map->map[map->p[Y]][map->p[X]] = '0';
		map->p[Y] += y;
		map->p[X] += x;
		map->map[map->p[Y]][map->p[X]] = 'P';
		move++;
	}
	change_dir(mlx->img, y, x);
	num = ft_itoa(move);
	if (!num)
		error_and_exit_mlx("malloc failed", 2, mlx);
	set_window(mlx, mlx->map, num);
	free(num);
}

int	key(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		error_and_exit_mlx("Premature game endation?", 2, mlx);
	if (keycode == XK_w || keycode == XK_W)
		move(mlx, -1, 0);
	if ((keycode == XK_A || keycode == XK_a))
		move(mlx, 0, -1);
	if (keycode == XK_S || keycode == XK_s)
		move(mlx, 1, 0);
	if (keycode == XK_d || keycode == XK_D)
		move(mlx, 0, 1);
	return (1);
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

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;
	t_img	img;

	if (argc < 2)
		return (ft_putendl_fd("Map file not found!", 2), 1);
	if (argc > 2)
		return (ft_putendl_fd("Too many arguments!", 2), 1);
	ft_bzero(&map, sizeof(map));
	ft_bzero(&mlx, sizeof(mlx));
	ft_bzero(&img, sizeof(img));
	map.bytes_read = -1;
	map.fd = -1;
	read_map(&map, argv[1]);
	mlx.map = &map;
	mlx.img = &img;
	init_window(&mlx);
	error_and_exit("lol", 1, &map);
	return (0);
}
