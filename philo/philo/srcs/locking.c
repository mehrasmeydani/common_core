/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:28:58 by megardes          #+#    #+#             */
/*   Updated: 2025/11/08 21:29:23 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ml(t_mutex *in)
{
	return (pthread_mutex_lock(in));
}

int	mu(t_mutex *in)
{
	return (pthread_mutex_unlock(in));
}
