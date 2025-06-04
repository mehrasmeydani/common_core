/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:05:26 by megardes          #+#    #+#             */
/*   Updated: 2025/06/04 15:02:02 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

int	g_pending = 0;

void	get_respond(int signum, siginfo_t *new, void *old)
{
	g_pending = 0;
	(void)old;
	(void)new;
	if (signum == SIGUSR2)
		return (ft_putendl_fd("Server recieved message succesfully", 1));
}

void	send_message(char *in, pid_t pid)
{
	ssize_t	i;
	ssize_t	bit;
	ssize_t	len;
	t_uc	c;

	len = ft_strlen(in);
	i = -1;
	while (++i <= len)
	{
		c = in[i];
		bit = -1;
		while (++bit < 8)
		{
			g_pending = 1;
			if (c & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			while (g_pending != 0 && g_pending++ < 5)
				sleep(1);
			if (g_pending == 6)
				return (ft_putendl_fd("No respond from server in time", 2));
			c = c >> 1;
		}
	}
}

int	main(int argc, char **argv)
{
	ssize_t				i;
	struct sigaction	sig;

	i = -1;
	if (argc != 3)
		return (ft_putendl_fd("Error: ./client <server_pid> <message>", 2), 1);
	while (argv[1][++i])
		if (!ft_isdigit(argv[1][i]))
			return (ft_putendl_fd("Error: invalid pid", 2), 1);
	sig.sa_sigaction = &get_respond;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigemptyset(&(sig.sa_mask)))
		return (ft_putendl_fd("sigemptyset failed", 2), 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	send_message(argv[2], ft_atoi(argv[1]));
}
