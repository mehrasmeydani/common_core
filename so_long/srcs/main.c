/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:18 by megardes          #+#    #+#             */
/*   Updated: 2025/06/25 12:31:57 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	collect(t_mlx *mlx, ssize_t y, ssize_t x, ssize_t *move)
{
	t_map	*map;

	map = mlx->map;
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
		*move = *move + 1;
	}
}

void	move(t_mlx *mlx, ssize_t y, ssize_t x)
{
	t_map			*map;
	char			*num;
	static ssize_t	move = 0;

	map = mlx->map;
	if (map->map[map->p[Y] + y][map->p[X] + x] == 'E' && map->collect == 0)
		error_and_exit_mlx("Come back soon", 1, mlx);
	collect(mlx, y, x, &move);
	change_dir(mlx->img, y, x);
	num = ft_itoa(move);
	if (!num)
		error_and_exit_mlx("malloc failed", 2, mlx);
	ft_putstr_fd("move count: ", 1);
	ft_putendl_fd(num, 1);
	set_window(mlx, mlx->map, num);
	free(num);
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
