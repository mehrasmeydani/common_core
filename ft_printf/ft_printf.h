/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:38:32 by megardes          #+#    #+#             */
/*   Updated: 2025/04/22 16:23:28 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <string.h>

# define CHAR_P char *
# define CHAR char
# define U_LL unsigned long long
# define INT int
# define U_INT unsigned int

int ft_printf(const char *str, ...);

#endif