/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:04:18 by megardes          #+#    #+#             */
/*   Updated: 2025/05/11 21:03:13 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	init_map(t_map *map)
{
	map->r[0] = 0;
	map->r[1] = 0;
	map->x = 0;
	map->y = 0;
	map->p = 0;
	map->c = 0;
	map->e = 0;
	map->map = NULL;
	map->bytes_read = -1;
}

void	error_and_exit(char *error, int fd)
{
	ft_putendl_fd(error, fd);
}

void	map_error(t_map *map, int fd)
{
	if (map->bytes_read == -1)
		return (close(fd), error_and_exit("ERROR! Cannot read file!", 2));
	if (map->bytes_read == 0 && map->r[0] != '\n')
		return (close(fd), error_and_exit("ERROR! No new line at EOF!", 2));
	if (map->r[0] != 'p' && map->r[0] != 'e' && map->r[0] != 'c'
		&& map->r[0] != '0' && map->r[0] != '1' && map->r[0] != '\n')	
		return (close(fd), error_and_exit("ERROR! Invalid character in file!", 2));
	if (map->r[0] == 'p')
		map->p++;
	if (map->r[0] == 'e')
		map->e++;
	if (map->r[0] == 'c')
		map->c++;
	if (map->p > 1 || map->e > 1)
		return (close(fd), error_and_exit("ERROR! Too many players or exits in file!", 2));
}

void	flood_fill(t_map *map, ssize_t x, ssize_t y)
{
	
}

void	create_map(t_map *map, char *str)
{
	ssize_t	i;
	int		fd;

	i = -1;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (error_and_exit("ERROR! Cannot open file!", 2));
	map->map = (char **)ft_calloc(map->y + 1, sizeof(char *));
	if (!map->map)
		return (error_and_exit("ERROR! Malloc fail!", 2));
	map->map_copy = (char **)ft_calloc(map->y + 1, sizeof(char *));
	if (!map->map)
		return (error_and_exit("ERROR! Malloc fail!", 2)); // free
	while (++i < map->y)
	{
		map->map[i] = (char *)ft_calloc(map->x + 1, sizeof(char));
		if (!map->map[i])
			return(close(fd), error_and_exit("ERROR! Malloc fail!", 2)); // free
		map->bytes_read = read(fd, map->map[i], map->x);
		if (map->bytes_read == -1)
			return (close(fd), error_and_exit("ERROR! Cannot read file!", 2)); // free
		map->map_copy[i] = ft_strdup(map->map);
		if (!map->map_copy[i])
			return (close(fd), error_and_exit("ERROR! Malloc fail!", 2)); // free
	}
	map->x -= 1;
	close(fd);
	flood_fill(map);
}

void	read_map(t_map *map, char *str)
{
	int	fd;

	if (!ft_strnstr(str, ".ber", ft_strlen(str)))
		return (error_and_exit("ERROR! Map file not '.ber'!", 2));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (error_and_exit("ERROR! Cannot open file!", 2));
	while (map->bytes_read != 0)
	{
		map->bytes_read = read(fd, map->r, 1);
		map_error(map, fd);
		if (map->bytes_read == 0)
			break ;
		map->x++;
		if (map->r[0] == '\n' && ++map->y)
			if (map->x % map->y != 0)
				return (close(fd), error_and_exit("ERROR! Map not square!", 2));
	}
	close(fd);
	if (map->c < 1)
		return (error_and_exit("ERROR! No collectables in file!", 2));
	map->x = map->x / map->y;
	create_map(map, str);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc < 2)
		return (ft_putendl_fd("ERROR! Map file not found!", 2), 1);
	if (argc > 2)
		return (ft_putendl_fd("ERROR! Too many arguments!", 2), 1);
	init_map(&map);
	read_map(&map, argv[1]);
	return (0);
}
