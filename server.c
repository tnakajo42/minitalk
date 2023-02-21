/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:11:54 by tnakajo           #+#    #+#             */
/*   Updated: 2023/02/21 23:08:42 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_server(int signal, siginfo_t *info, void *s)
{
	static char		c;
	static int		bit;
	static pid_t	client_pid;

	(void)s;
	if (!client_pid)
		client_pid = info->si_pid;
	if (signal == SIGUSR1)
		c = c | (1 << bit);
	bit++;
	if (bit == 8 && c)
	{
		write(1, &c, 1);
		if (c == 3)
			kill(client_pid, SIGUSR1);
		else
			kill(client_pid, SIGUSR2);
		client_pid = 0;
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("Process ID: %d\n", getpid());
	sig.sa_sigaction = ft_server;
	sig.sa_flags = SA_SIGINFO;
	while (42)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause ();
	}
	return (0);
}
