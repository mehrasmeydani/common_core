/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:38:04 by megardes          #+#    #+#             */
/*   Updated: 2025/04/22 16:54:29 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putd(unsigned long long a, int c)
{
	(void)c;
	ft_putnbr_fd((int)a, 1);
	return (2);
}

int	print(const char *str, int *i, va_list args)
{
	int	out;

	out = 0;
	if (str[(*i)] == '%' && str[(*i) + 1] == 'c' && ++(*i))
		out += ft_putchar_fd(va_arg(args, int), 1);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 's' && ++(*i))
		out += ft_putstr_fd(va_arg(args, char *), 1);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'p' && ++(*i))
		out += ft_putd(va_arg(args, unsigned long long), 2);
	else if (str[(*i)] == '%' && (str[(*i) + 1] == 'd'
			|| str[(*i) + 1] != 'd') && ++(*i))
		out += ft_putd(va_arg(args, int), 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'u' && ++(*i))
		out += ft_putd(va_arg(args, unsigned int), 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'x' && ++(*i))
		out += ft_putd(va_arg(args, int), 1);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'X' && ++(*i))
		out += ft_putd(va_arg(args, unsigned int), 1);
	else if (str[(*i)] == '%' && str[(*i) + 1] == '%' && ++(*i))
		out += ft_putchar_fd(str[(*i)], 1);
	else
		out += ft_putchar_fd(str[(*i)], 1);
	return (out);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		out;

	i = -1;
	out = 0;
	va_start(args, str);
	while (str[++i])
		out += print(str, &i, args);
	va_end(args);
	return (out);
}
