/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:18 by megardes          #+#    #+#             */
/*   Updated: 2025/05/12 21:47:25 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	ft_free(char **in)
{
	ssize_t i;

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
		{
			close(map->fd);
			map->fd = -1;
		}
		if (map->map)
		{
			ft_free(map->map);
			map->map = NULL;
		}
		if (map->map_copy)
		{
			ft_free(map->map_copy);
			map->map_copy = NULL;
		}
	}
	ft_putendl_fd(error, fd);
	exit(1);
}

void	flood_fill(t_map *map, ssize_t x, ssize_t y)
{
	
	if (x == -1 || y == -1 || x == map->x || y == map->y || map->map_copy[y][x] == '1')
		return ;
	map->map_copy[y][x] = '1';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x , y + 1);
	flood_fill(map, x , y - 1);	
}

void	find_player(t_map *map, ssize_t *y, ssize_t *x)
{
	*y = -1;
	while (++*y < map->y)
	{
		*x = -1;
		while (++*x < map->x)
			if (map->map[*y][*x] == 'p')
				return ;
	}
}

void	map_check(t_map *map)
{
	ssize_t	x;
	ssize_t y;

	map->i = -1;
	while (++map->i < map->y - 1)
		if (map->map[map->i][map->x - 1] != '1' || map->map[map->i][0] != '1')
			return (error_and_exit("Walls are not place correctly!", 2, map));
	map->i = -1;
	while (map->map[map->y - 1][++map->i])
		if (map->map[map->y - 1][map->i] != '1' && map->map[map->y - 1][map->i] != '\n')
			return (error_and_exit("Invalid character in last line!", 2, map));
	find_player(map, &y, &x);
	flood_fill(map, x, y);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		while (++x < map->x)
			if (map->map_copy[y][x] != '1')
				return (error_and_exit("Game cannot be finished!", 2, map));
			
	}
}

void	create_map(t_map *map, char *str)
{
	map->i = -1;
	map->fd = open(str, O_RDONLY);
	if (map->fd == -1)
		return (error_and_exit("Cannot open file!", 2, map));
	map->map = (char **)ft_calloc(map->y + 1, sizeof(char *));
	map->map_copy = (char **)ft_calloc(map->y + 1, sizeof(char *));
	if (!map->map_copy || !map->map)
		return (error_and_exit("Malloc fail!", 2, map));
	while (++map->i < map->y)
	{
		map->map[map->i] = (char *)ft_calloc(map->x + 1, sizeof(char));
		if (!map->map[map->i])
			return(error_and_exit("Malloc fail!", 2, map));
		map->bytes_read = read(map->fd, map->map[map->i], map->x);
		if (map->bytes_read == -1)
			return (error_and_exit("Cannot read file!", 2, map));
		map->map_copy[map->i] = ft_strdup(map->map[map->i]);
		if (!map->map_copy[map->i])
			return (error_and_exit("Malloc fail!", 2, map));
	}
	map->x -= 1;
	close(map->fd);
	map_check(map);
}

void	map_error(t_map *map)
{
	if (map->bytes_read == -1)
		return (error_and_exit("Cannot read file!", 2, map));
	if (map->bytes_read == 0 && map->r[0] != '\n')
		return (error_and_exit("No new line at EOF!", 2, map));
	if (map->r[0] != 'p' && map->r[0] != 'e' && map->r[0] != 'c'
		&& map->r[0] != '0' && map->r[0] != '1' && map->r[0] != '\n')	
		return (error_and_exit("Invalid character in file!", 2, map));
	if (map->y == 0 && (map->r[0] != '1' && map->r[0] != '\n'))
		return (error_and_exit("Invalid character in first line!", 2, map));
	if (map->r[0] == 'p')
		map->player++;
	if (map->r[0] == 'e')
		map->exit++;
	if (map->r[0] == 'c')
		map->collect++;
	if (map->player > 1 || map->exit > 1)
		return (error_and_exit("Too many players or exits in file!", 2, map));
	if (map->y == 0 && map->r[0] == '\n')
		map->x_first = map->x + 1;
}

void	read_map(t_map *map, char *str)
{
	if (!ft_strnstr(str, ".ber", ft_strlen(str)))
		return (error_and_exit("Map file not '.ber'!", 2, map));
	map->fd = open(str, O_RDONLY);
	if (map->fd == -1)
		return (error_and_exit("Cannot open file!", 2, map));
	while (map->bytes_read != 0)
	{
		map->bytes_read = read(map->fd, map->r, 1);
		map_error(map);
		if (map->bytes_read == 0)
			break ;
		map->x++;
		if (map->r[0] == '\n' && ++map->y)
			if (map->x % map->y != 0 || map->x_first != map->x / map->y)
				return (error_and_exit("Map not square!", 2, map));
	}
	close(map->fd);
	map->fd = -1;
	map->x = map->x / map->y;
	if (map->collect < 1 || map->player < 1 || map->exit < 1 || map->y * map->x < 18)
		return (error_and_exit("No collectables/player/exit in file!", 2, map));
	create_map(map, str);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	init_window(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx, 1920, 1080, "Hello world!");
	mlx->img->img = mlx_new_image(mlx->mlx, 1920, 1080);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
	my_mlx_pixel_put(mlx->img, 5, 5, 0x00FFFF00);
	my_mlx_pixel_put(mlx->img, 5, 6, 0x00FFFF00);
	my_mlx_pixel_put(mlx->img, 5, 7, 0x00FFFF00);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_window, mlx->img->img, 0, 0);
	mlx_loop(mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_mlx	mlx;
	t_data	img;

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
	//run_game();
	error_and_exit("lol", 1, &map);
	return (0);
}
