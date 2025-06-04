/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:13:18 by megardes          #+#    #+#             */
/*   Updated: 2025/06/04 14:21:49 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	flood_fill(t_map *map, ssize_t x, ssize_t y)
{
	if (x == -1 || y == -1 || x == map->x || y == map->y
		|| map->map_copy[y][x] == '1')
		return ;
	if (map->map_copy[y][x] == 'E' || map->map_copy[y][x] == 'O')
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
