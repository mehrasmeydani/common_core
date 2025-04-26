/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:30:48 by mehras            #+#    #+#             */
/*   Updated: 2025/04/26 15:56:10 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	ssize_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *s = malloc(2147483650);
	memset(s, 0, 2147483650);
	memset(s, 'c', 2147483649);

	printf("%zu", ft_strlen(s));

	//printf("yay!");
}