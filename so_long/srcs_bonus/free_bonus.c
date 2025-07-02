/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:14:54 by megardes          #+#    #+#             */
/*   Updated: 2025/07/02 16:18:44 by megardes         ###   ########.fr       */
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
	exit(fd - 1);
}

void	free_img(void *mlx, t_img *img)
{
	if (img->collect)
		mlx_destroy_image(mlx, img->collect);
	if (img->player_up)
		mlx_destroy_image(mlx, img->player_up);
	if (img->player_left)
		mlx_destroy_image(mlx, img->player_left);
	if (img->player_down)
		mlx_destroy_image(mlx, img->player_down);
	if (img->player_right)
		mlx_destroy_image(mlx, img->player_right);
	if (img->empty)
		mlx_destroy_image(mlx, img->empty);
	if (img->exit)
		mlx_destroy_image(mlx, img->exit);
	if (img->o_exit)
		mlx_destroy_image(mlx, img->o_exit);
	if (img->wall)
		mlx_destroy_image(mlx, img->wall);
	if (img->enemy)
		mlx_destroy_image(mlx, img->enemy);
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

int	exit_mlx(t_mlx *mlx)
{
	error_and_exit_mlx("done?no leaks?", 1, mlx);
	return (1);
}
