/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:05:24 by megardes          #+#    #+#             */
/*   Updated: 2025/05/30 11:22:24 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minitalk.h"

ssize_t	pow_2(ssize_t i)
{
	if (i == 0)
		return (1);
	return (2 * pow_2(i - 1));
}

char	*recalloc_quad(char	*in, ssize_t pow)
{
	char	*out;

	if (!in)
		return ((char *)ft_calloc(pow_2(pow), 1));
	out = (char	*)ft_calloc(pow_2(pow), 1);
	if (!out)
		return (free(in), NULL);
	ft_strlcpy(out, in, ft_strlen(in) + 1);
	free(in);
	return (out);
}

void	get_bit(int signum, siginfo_t *new, void *old)
{
	static char 	*out = NULL;
	static ssize_t	bits = -1;
	static ssize_t	calls = 0;
	static ssize_t	pow = 1;

	bits++;
	(void)old;
	if (calls == 0 || calls + 2 >= pow_2(pow))
		out = recalloc_quad(out, ++pow);
	if (!out)
		return (ft_putendl_fd("malloc failed!", 2), exit(1));
	out[calls] += (signum == SIGUSR2) * (1 << bits);
	if (bits == 7)
	{
		bits = -1;
		if (!out[calls])
			return (ft_putstr_fd(out, 1), free(out), out = NULL,
					calls = 0, pow = 1, (void)kill(new->si_pid, SIGUSR1));
		else
			kill(new->si_pid, SIGUSR2);
		calls++;
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = &get_bit;
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigemptyset(&(sig.sa_mask)))
		return (ft_putendl_fd("sigemptyset failed", 2), 1);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("", 1);
	while (1)
		pause();
	return (0);
}