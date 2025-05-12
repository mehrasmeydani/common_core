/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:29:54 by megardes          #+#    #+#             */
/*   Updated: 2025/05/12 17:17:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t dsize);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif