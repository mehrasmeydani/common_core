/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:46:25 by megardes          #+#    #+#             */
/*   Updated: 2025/06/25 12:25:39 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

static void	init_img2(t_mlx *mlx, t_img *img, int img_width, int img_height)
{
	img->player_up = mlx_xpm_file_to_image(mlx->mlx, "./xpm/up.xpm",
			&img_width, &img_height);
	if (!img->player_up || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->player_left = mlx_xpm_file_to_image(mlx->mlx, "./xpm/left.xpm",
			&img_width, &img_height);
	if (!img->player_left || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->player_right = mlx_xpm_file_to_image(mlx->mlx, "./xpm/right.xpm",
			&img_width, &img_height);
	if (!img->player_right || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->enemy = mlx_xpm_file_to_image(mlx->mlx, "./xpm/enemy.xpm",
			&img_width, &img_height);
	if (!img->enemy || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->o_exit = mlx_xpm_file_to_image(mlx->mlx, "./xpm/door_open.xpm",
			&img_width, &img_height);
	if (!img->o_exit || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->player_status = img->player_down;
	img->exit_status = img->exit;
}

void	init_img(t_mlx *mlx, t_img *img, int img_width, int img_height)
{
	img->collect = mlx_xpm_file_to_image(mlx->mlx, "./xpm/collect.xpm",
			&img_width, &img_height);
	if (!img->collect || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->player_down = mlx_xpm_file_to_image(mlx->mlx, "./xpm/down.xpm",
			&img_width, &img_height);
	if (!img->player_down || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->empty = mlx_xpm_file_to_image(mlx->mlx, "./xpm/empty.xpm",
			&img_width, &img_height);
	if (!img->empty || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->wall = mlx_xpm_file_to_image(mlx->mlx, "./xpm/wall.xpm",
			&img_width, &img_height);
	if (!img->wall || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	img->exit = mlx_xpm_file_to_image(mlx->mlx, "./xpm/door.xpm",
			&img_width, &img_height);
	if (!img->exit || img_height != XPM_SIZE || img_width != XPM_SIZE)
		error_and_exit_mlx("XPM file's size/name/permissions are bad!", 2, mlx);
	init_img2(mlx, img, img_width, img_height);
}
