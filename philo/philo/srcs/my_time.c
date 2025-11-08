/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:41:28 by megardes          #+#    #+#             */
/*   Updated: 2025/11/08 21:41:53 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

unsigned int	my_time(void)
{
	t_tm	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((unsigned int)time.tv_usec / 100 + (time.tv_sec % 100000 * 10000));
}
