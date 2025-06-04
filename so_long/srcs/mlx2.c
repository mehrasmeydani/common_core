/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:37:46 by megardes          #+#    #+#             */
/*   Updated: 2025/06/04 13:37:56 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

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
