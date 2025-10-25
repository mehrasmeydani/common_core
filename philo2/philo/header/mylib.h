/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:59:39 by megardes          #+#    #+#             */
/*   Updated: 2025/08/13 14:25:47 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYLIB_H
# define MYLIB_H

# include "philo.h"

typedef unsigned char	t_uc;

void	*not_calloc(size_t nmemb, size_t size);
void	not_bzero(void *s, size_t n);

#endif