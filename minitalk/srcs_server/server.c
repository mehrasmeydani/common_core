/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:05:24 by megardes          #+#    #+#             */
/*   Updated: 2025/05/26 14:58:59 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

int	g_num;

void	*ft_recalloc()
{
	
}

void	sig_handler(int	sig)
{
	if (sig)
		g_num++;	
}

int	main(void)
{
	int				pid;
	unsigned char	*out;
	struct sigaction	sig;

	g_num = 0;
	pid = getpid();
}