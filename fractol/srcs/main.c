/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:20:50 by megardes          #+#    #+#             */
/*   Updated: 2025/07/02 16:08:48 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

double	my_map(int a, double min, double max)
{
	return ((double)(a / (SIZE / (max - min)) + min));
}

int	is_inrange(t_mandel *mandel)
{
	return (mandel->a_new + mandel->b_new < 2
		&& mandel->a_new + mandel->b_new > -2);
}

double	pow2(double a)
{
	return (a * a);
}

void	free_and_err(t_mlx *mlx, char *str, int fd)
{
	if (mlx)
	{
		if (mlx->mlx)
		{
			if (mlx->win)
				mlx_destroy_window(mlx->mlx, mlx->win);
			if (mlx->img)
				mlx_destroy_image(mlx->mlx, mlx->img);
			mlx_destroy_display(mlx->mlx);
			free(mlx->mlx);
		}
	}
	if (str)
	ft_putendl_fd(str, fd);
	exit(fd - 1);
}

void	put_color(t_mlx *mlx, ssize_t x, ssize_t y, ssize_t color)
{
	char			*dst;

	dst = mlx->addr + (y * mlx->ll + x * (mlx->bpp / 8));
	if (color == -1)
		*(unsigned int*)dst = 0x00000000;
	else if (color != MAX_ITER)
		*(unsigned int*)dst = color * 0x00ffffff / MAX_ITER;
	else
		*(unsigned int*)dst = (color + 1) * 0x00ffffff / MAX_ITER;
}

void	cal(t_mlx *mlx, t_mandel *mp)
{
	mp->x = -1;
	while (++mp->x < SIZE)
	{
		mp->y = -1;
		while (++mp->y < SIZE)
		{
			mp->a = my_map(mp->x, mp->x_min, mp->x_max);
			mp->b = my_map(mp->y, mp->y_min, mp->y_max);
			mp->iter = -1;
			mp->a_new = mp->a;
			mp->b_new = mp->b;
			while (++mp->iter < MAX_ITER && is_inrange(mp))
			{
				mp->a_tmp = pow2(mp->a_new) - pow2(mp->b_new) + mp->a;
				mp->b_tmp = 2 * mp->a_new * mp->b_new + mp->b;
				mp->a_new = mp->a_tmp;
				mp->b_new = mp->b_tmp;
			}
			if (mp->iter == MAX_ITER)
				put_color(mlx, mp->x, mp->y, -1);
			else
				put_color(mlx, mp->x, mp->y, mp->iter);
		}
	}
}

void	cal_j(t_mlx *mlx, t_mandel *mp)
{
	mp->x = -1;
	while (++mp->x < SIZE)
	{
		mp->y = -1;
		while (++mp->y < SIZE)
		{
			mp->a = my_map(mp->x, mp->x_min, mp->x_max) + mp->aj;
			mp->b = my_map(mp->y, mp->y_min, mp->y_max) + mp->bj;
			mp->iter = -1;
			mp->a_new = mp->a;
			mp->b_new = mp->b;
			while (++mp->iter < MAX_ITER && is_inrange(mp))
			{
				mp->a_tmp = pow2(mp->a_new) - pow2(mp->b_new) + mp->aj;
				mp->b_tmp = 2 * mp->a_new * mp->b_new + mp->bj;
				mp->a_new = mp->a_tmp;
				mp->b_new = mp->b_tmp;
			}
			put_color(mlx, mp->x, mp->y, mp->iter);
		}
	}
}

int	exit_mlx(t_mlx *mlx)
{
	free_and_err(mlx, "closure", 1);
	return (1);
}

void	move(t_mlx *mlx, int x, int y)
{
	mlx->mb->x_max += (double)y * 0.1;
	mlx->mb->x_min += (double)y * 0.1;
	mlx->mb->y_max += (double)x * 0.1;
	mlx->mb->y_min += (double)x * 0.1;
	ft_bzero(mlx->addr, sizeof(mlx->addr));
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	cal(mlx, mlx->mb);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	key(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		free_and_err(mlx, "closure", 1);
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

int	key2(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		free_and_err(mlx, "closure", 1);
	return (1);
}

void	zoom(t_mlx *mlx, double i, int j)
{
	(void)i;
	mlx->mb->x_max *= i;
	mlx->mb->x_min *= i;
	mlx->mb->y_max *= i;
	mlx->mb->y_min *= i;
	if (j == 0)
		cal(mlx, mlx->mb);
	else
		cal_j(mlx, mlx->mb);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	scroll(int keycode, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (keycode == 4)
		zoom(mlx, 0.9, 0);
	if (keycode == 5)
		zoom(mlx, 1.1, 0);
	return (1);
}

int	scroll2(int keycode, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (keycode == 4)
		zoom(mlx, 0.9, 1);
	if (keycode == 5)
		zoom(mlx, 1.1, 1);
	return (1);
}

void	hook_all(t_mlx *mlx)
{
	mlx_hook(mlx->win, 17, 0, exit_mlx, mlx);
	mlx_hook(mlx->win, 2, (1L << 0), key, mlx);
	mlx_mouse_hook(mlx->win, scroll, mlx);
}

void	mandelbrot(t_mlx	*mlx)
{
	t_mandel	mp;

	mlx->mb = &mp;
	mp.x_min = -2;
	mp.x_max = 2;
	mp.y_min = -2;
	mp.y_max = 2;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (free_and_err(NULL, "mlx failed", 2));
	mlx->win = mlx_new_window(mlx->mlx, SIZE, SIZE, "fractol");
	if (!mlx->win)
		return (free_and_err(mlx, "win failed", 2));
	mlx->img = mlx_new_image(mlx->mlx, SIZE, SIZE);
	if (!mlx->img)
		return (free_and_err(mlx, "img failed", 2));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->endian);
	if (!mlx->addr)
		return (free_and_err(mlx, "addr failed", 2));
	ft_bzero(mlx->addr, sizeof(mlx->addr));
	cal(mlx, &mp);
	hook_all(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}

void	julia(t_mlx *mlx, char *a, char *b)
{
	t_mandel	mp;

	mlx->mb = &mp;
	mp.x_min = -1.2;
	mp.x_max = 2.8;
	mp.y_min = -2;
	mp.y_max = 2;
	mp.aj = atof(a);
	mp.bj = atof(b);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (free_and_err(NULL, "mlx failed", 2));
	mlx->win = mlx_new_window(mlx->mlx, SIZE, SIZE, "fractol");
	if (!mlx->win)
		return (free_and_err(mlx, "win failed", 2));
	mlx->img = mlx_new_image(mlx->mlx, SIZE, SIZE);
	if (!mlx->img)
		return (free_and_err(mlx, "img failed", 2));
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ll, &mlx->endian);
	if (!mlx->addr)
		return (free_and_err(mlx, "addr failed", 2));
	ft_bzero(mlx->addr, sizeof(mlx->addr));
	cal_j(mlx, &mp);
	mlx_hook(mlx->win, 17, 0, exit_mlx, mlx);
	mlx_hook(mlx->win, 2, (1L << 0), key2, mlx);
	mlx_mouse_hook(mlx->win, scroll2, mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx_loop(mlx->mlx);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc < 2)
		return (ft_putendl_fd("use one of the following formats:", 2),
			ft_putendl_fd("./fractol mandelbrot", 2),
			ft_putendl_fd("./fractol julia <value> <value>", 2), 1);
	ft_bzero(&mlx, sizeof(mlx));
	if (!ft_strncmp("mandelbrot", argv[1], 11) && argc == 2)
		mandelbrot(&mlx);
	else if (!ft_strncmp("julia", argv[1], 10) && argc == 4)
		julia(&mlx, argv[2], argv[3]);
	else
		return (ft_putendl_fd("use one of the following formats:", 2),
			ft_putendl_fd("./fractol mandelbrot", 2),
			ft_putendl_fd("./fractol julia <value> <value>", 2), 1);
}
