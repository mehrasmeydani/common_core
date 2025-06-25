/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:20:15 by megardes          #+#    #+#             */
/*   Updated: 2025/06/25 21:06:43 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <X11/keysym.h>

//# include <stdio.h>

# define MAX_ITER 50
# define SIZE 1080

typedef struct s_mandel
{
	double	y_max;
	double	x_max;
	double	y_min;
	double	x_min;
	double	a;
	double	b;
	double	aj;
	double	bj;
	double	a_new;
	double	b_new;
	double	a_tmp;
	double	b_tmp;
	ssize_t	x;
	ssize_t	y;
	ssize_t	iter;
}	t_mandel;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		*addr;
	void		*img;
	int			bpp;
	int			ll;
	int			endian;
	t_mandel	*mb;
}	t_mlx;


#endif