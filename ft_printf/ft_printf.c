/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:38:04 by megardes          #+#    #+#             */
/*   Updated: 2025/04/23 12:21:42 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_pf(char *str)
{
	if (!str)
		return ((int)write(1, "(null)", 6));
	return ((int)write(1, str, ft_strlen(str)));
}

void	ft_putd(long long a, int c, int *out, int run)
{
	const char	*b[3] = {"0123456789", "0123456789abcdef", "0123456789abcdef"};

	if (a == 0 && c == 2)
		*out += write(1, "(nil)", 1);
	else if (c == 2 && run == 0)
		*out += write(1, "0x", 2);
	if (a < 0)
	{
		a = -a;
		*out += write(1, "-", 2);
		ft_putd(a, c, out, run + 1);
	}
	else if (a > (long long)ft_strlen(b[c]))
	{
		ft_putd(a / ft_strlen(b[c]), c, out, run + 1);
		ft_putd(a % ft_strlen(b[c]), c, out, run);
	}
	else
		*out += write (1, &b[c][a], 1);
}

int	print(const char *str, int *i, va_list args)
{
	int	out;

	out = 0;
	if (str[(*i)] == '%' && str[(*i) + 1] == 'c' && ++(*i))
		out += ft_putchar_fd(va_arg(args, int), 1);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 's' && ++(*i))
		out += ft_putstr_pf(va_arg(args, char *));
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'p' && ++(*i))
		ft_putd(va_arg(args, unsigned long long), 2, &out, 0);
	else if (str[(*i)] == '%' && (str[(*i) + 1] == 'd'
			|| str[(*i) + 1] != 'd') && ++(*i))
		ft_putd(va_arg(args, int), 0, &out, 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'u' && ++(*i))
		ft_putd(va_arg(args, unsigned int), 0, &out, 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'x' && ++(*i))
		ft_putd(va_arg(args, int), 1, &out, 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'X' && ++(*i))
		ft_putd(va_arg(args, unsigned int), 1, &out, 0);
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
