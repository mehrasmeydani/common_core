/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:18 by megardes          #+#    #+#             */
/*   Updated: 2025/05/13 22:28:11 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_free(char **in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		free(in[i]);
	free(in);
}

void	error_and_exit(char *error, int fd, t_map *map)
{
	if (map)
	{
		if (map->fd != -1)
			close(map->fd);
		if (map->map)
			ft_free(map->map);
		if (map->map_copy)
			ft_free(map->map_copy);
	}
	if (fd == 2)
		ft_putendl_fd("ERROR", fd);
	ft_putendl_fd(error, fd);
	exit(1);
}

void	free_img(void *mlx, t_img *img)
{
	if (img->collect)
		mlx_destroy_image(mlx, img->collect);
	if (img->player)
		mlx_destroy_image(mlx, img->player);
	if (img->empty)
		mlx_destroy_image(mlx, img->empty);
	if (img->exit)
		mlx_destroy_image(mlx, img->exit);
	if (img->wall)
		mlx_destroy_image(mlx, img->wall);
}

void	error_and_exit_mlx(char *error, int fd, t_mlx *mlx)
{
	if (mlx)
	{
		if (mlx->mlx)
		{
			if (mlx->win)
				mlx_destroy_window(mlx->mlx, mlx->win);
			if (mlx->img)
				free_img(mlx->mlx, mlx->img);
			mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
		error_and_exit(error, fd, mlx->map);
	}
}

void	flood_fill(t_map *map, ssize_t x, ssize_t y)
{
	if (x == -1 || y == -1 || x == map->x || y == map->y
		|| map->map_copy[y][x] == '1')
		return ;
	if (map->map_copy[y][x] == 'E')
		return ((void)(map->map_copy[y][x] = '1'));
	map->map_copy[y][x] = '1';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

void	find_player(t_map *map, ssize_t *y, ssize_t *x, char c)
{
	*y = -1;
	while (++*y < map->y)
	{
		*x = -1;
		while (++*x < map->x)
			if (map->map[*y][*x] == c)
				return ;
	}
}

void	flood_worked(t_map *map)
{
	ssize_t	x;
	ssize_t	y;

	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
		{
			if (map->map_copy[y][x] != '1' && map->map_copy[y][x] != '0')
				error_and_exit("Game cannot be finished!", 2, map);
			else
				map->map_copy[y][x] = map->map[y][x];
		}
	}
}

void	map_check(t_map *map)
{
	map->i = -1;
	while (++map->i < map->y - 1)
		if (map->map[map->i][map->x - 1] != '1' || map->map[map->i][0] != '1')
			error_and_exit("Walls are not place correctly!", 2, map);
	map->i = -1;
	while (map->map[map->y - 1][++map->i])
		if (map->map[map->y - 1][map->i] != '1'
			&& map->map[map->y - 1][map->i] != '\n')
			error_and_exit("Invalid character in last line!", 2, map);
	find_player(map, &map->p[Y], &map->p[X], 'P');
	find_player(map, &map->e[Y], &map->e[X], 'E');
	flood_fill(map, map->p[X], map->p[Y]);
	flood_worked(map);
}

void	create_map(t_map *map, char *str)
{
	map->i = -1;
	map->fd = open(str, O_RDONLY);
	if (map->fd == -1)
		error_and_exit("Cannot open file!", 2, map);
	map->map = (char **)ft_calloc(map->y + 1, sizeof(char *));
	map->map_copy = (char **)ft_calloc(map->y + 1, sizeof(char *));
	if (!map->map_copy || !map->map)
		error_and_exit("Malloc fail!", 2, map);
	while (++map->i < map->y)
	{
		map->map[map->i] = (char *)ft_calloc(map->x + 1, sizeof(char));
		if (!map->map[map->i])
			error_and_exit("Malloc fail!", 2, map);
		map->bytes_read = read(map->fd, map->map[map->i], map->x);
		if (map->bytes_read == -1)
			error_and_exit("Cannot read file!", 2, map);
		map->map_copy[map->i] = ft_strdup(map->map[map->i]);
		if (!map->map_copy[map->i])
			error_and_exit("Malloc fail!", 2, map);
	}
	map->x -= 1;
	close(map->fd);
	map_check(map);
}

void	map_error(t_map *map)
{
	if (map->bytes_read == -1)
		error_and_exit("Cannot read file!", 2, map);
	if (map->bytes_read == 0 && map->r[0] != '\n')
		error_and_exit("No new line at EOF!", 2, map);
	if (map->r[0] != 'P' && map->r[0] != 'E' && map->r[0] != 'C'
		&& map->r[0] != '0' && map->r[0] != '1' && map->r[0] != '\n')
		error_and_exit("Invalid character in file!", 2, map);
	if (map->y == 0 && (map->r[0] != '1' && map->r[0] != '\n'))
		error_and_exit("Invalid character in first line!", 2, map);
	if (map->r[0] == 'P')
		map->player++;
	if (map->r[0] == 'E')
		map->exit++;
	if (map->r[0] == 'C')
		map->collect++;
	if (map->player > 1 || map->exit > 1)
		error_and_exit("Too many players or exits in file!", 2, map);
	if (map->y == 0 && map->r[0] == '\n')
		map->x_first = map->x + 1;
}

void	read_map(t_map *map, char *str)
{
	if (!ft_strnstr(str, ".ber", ft_strlen(str)))
		error_and_exit("Map file not '.ber'!", 2, map);
	map->fd = open(str, O_RDONLY);
	if (map->fd == -1)
		error_and_exit("Cannot open file!", 2, map);
	while (map->bytes_read != 0)
	{
		map->bytes_read = read(map->fd, map->r, 1);
		map_error(map);
		if (map->bytes_read == 0)
			break ;
		map->x++;
		if (map->r[0] == '\n' && ++map->y)
			if (map->x % map->y != 0 || map->x_first != map->x / map->y)
				error_and_exit("Map not square!", 2, map);
	}
	close(map->fd);
	map->fd = -1;
	map->x = map->x / map->y;
	if (map->collect < 1 || map->player < 1
		|| map->exit < 1 || map->y * map->x < 18)
		error_and_exit("No collectables/player/exit in file!", 2, map);
	create_map(map, str);
}

int	exit_mlx(t_mlx *mlx)
{
	error_and_exit_mlx("done?no leaks?", 1, mlx);
	return (1);
}

void	my_put_img(t_mlx *mlx, t_map *map, ssize_t x, ssize_t y)
{
	if (map->map[y][x] == 'P')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->player,
			x * XPM_SIZE, y * XPM_SIZE);
	if (map->map[y][x] == 'E')
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->exit,
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

void	set_window(t_mlx *mlx, t_map *map)
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
}

void	move(t_mlx *mlx, ssize_t y, ssize_t x)
{
	t_map	*map;

	map = mlx->map;
	if (map->map[map->p[Y] + y][map->p[X] + x] == 'E' && map->collect == 0)
		error_and_exit_mlx("Come back soon", 1, mlx);
	if (map->map[map->p[Y] + y][map->p[X] + x] == '0'
		|| map->map[map->p[Y] + y][map->p[X] + x] == 'C')
	{
		if (map->map[map->p[Y] + y][map->p[X] + x] == 'C')
			map->collect--; //open_door
		map->map[map->p[Y]][map->p[X]] = '0';
		map->p[Y] += y;
		map->p[X] += x;
		map->map[map->p[Y]][map->p[X]] = 'P';
	}
	//change direction
	//change steps
	set_window(mlx, mlx->map);
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

void	init_img(t_mlx *mlx, t_img *img, int img_width, int img_height)
{
	img->collect = mlx_xpm_file_to_image(mlx->mlx, "./xmp/collect.xpm",
			&img_width, &img_height);
	if (!img->collect || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->player = mlx_xpm_file_to_image(mlx->mlx, "./xmp/player_down.xpm",
			&img_width, &img_height);
	if (!img->player || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->empty = mlx_xpm_file_to_image(mlx->mlx, "./xmp/tiles.xpm",
			&img_width, &img_height);
	if (!img->empty || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->wall = mlx_xpm_file_to_image(mlx->mlx, "./xmp/wall.xpm",
			&img_width, &img_height);
	if (!img->wall || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->exit = mlx_xpm_file_to_image(mlx->mlx, "./xmp/door.xpm",
			&img_width, &img_height);
	if (!img->exit || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
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
	set_window(mlx, mlx->map);
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
