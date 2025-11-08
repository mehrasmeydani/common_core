/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:26:47 by megardes          #+#    #+#             */
/*   Updated: 2025/11/08 21:27:08 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/mylib.h"

void	ft_put_str(char *str, int fd)
{
	while (*str)
		write (fd, str++, 1);
}

void	ft_put_endl(char *str, int fd)
{
	while (*str)
		write (fd, str++, 1);
	write(fd, "\n", 1);
}

void	ft_putnbr(int i, int fd)
{
	if (i != 0)
		return (ft_putnbr(i / 10, fd),
			(void)write(fd, &"0123456789"[i % 10], 1));
}
