/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:11:39 by megardes          #+#    #+#             */
/*   Updated: 2025/05/30 16:12:31 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

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
