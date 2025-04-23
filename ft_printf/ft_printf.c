/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:38:04 by megardes          #+#    #+#             */
/*   Updated: 2025/04/23 14:28:38 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_pf(char *str)
{
	if (!str)
		return ((int)write(1, "(null)", 6));
	return ((int)write(1, str, ft_strlen(str)));
}

void	ft_putp(unsigned long long a, int *out, int run)
{
	if (a == 0 && run == 0)
	{
		*out += write(1, "(nil)", 5);
		return;
	}
	else if (run == 0)
		*out += write(1, "0x", 2);
	if (a >= 16)
	{
		ft_putp(a / 16, out, run + 1);
		ft_putp(a % 16, out, run + 1);
	}
	else
		*out += write (1, &"0123456789abcdef"[a], 1);
}

void	ft_putd(long long a, int c, int *out, int run)
{
	const char	*b[3] = {"0123456789", "0123456789abcdef", "0123456789ABCDEF"};

	if (a < 0)
	{
		a = -a;
		*out += write(1, "-", 1);
		ft_putd(a, c, out, run + 1);
	}
	else if (a >= (long long)ft_strlen(b[c]))
	{
		ft_putd(a / ft_strlen(b[c]), c, out, run + 1);
		ft_putd(a % ft_strlen(b[c]), c, out, run + 1);
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
		ft_putp(va_arg(args, unsigned long long), &out, 0);
	else if (str[(*i)] == '%' && (str[(*i) + 1] == 'd'
			|| str[(*i) + 1] == 'i') && ++(*i))
		ft_putd(va_arg(args, int), 0, &out, 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'u' && ++(*i))
		ft_putd(va_arg(args, unsigned int), 0, &out, 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'x' && ++(*i))
		ft_putd((unsigned int)va_arg(args, unsigned int), 1, &out, 0);
	else if (str[(*i)] == '%' && str[(*i) + 1] == 'X' && ++(*i))
		ft_putd(va_arg(args, unsigned int), 2, &out, 0);
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
