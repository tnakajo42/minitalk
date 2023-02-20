/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:10:59 by tnakajo           #+#    #+#             */
/*   Updated: 2023/02/20 18:51:29 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_client(int signal)
{
	static int	i;

	if (signal == SIGUSR2)
		i++;
	else
		ft_printf("★ Total Length from Server : %d\n", i);
}

static void	ft_send_bits(int pid, char c, int end)
{
	int			bit;
	static int	i;
	static int	ui;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
		// if (c < 0 || c > 127)
		if (c < 0)
			ui++;
	}
	if (c == 3 && end == 1)
		ft_printf("★ Total Length with Unicode: %i\n", i);
	if (ui == 0 || ui == 24)
	{
		i++;
		ui = 0;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		ft_printf("☆ Message You Will send    : \"%s\"\n", argv[2]);
		ft_printf("☆ The Length You Will send : %i\n", ft_strlen(argv[2]));
		while (argv[2][i] != '\0')
		{
			signal(SIGUSR1, ft_client);
			signal(SIGUSR2, ft_client);
			ft_send_bits(pid, argv[2][i++], 0);
		}
		ft_send_bits(pid, 3, 1);
		signal(SIGUSR1, ft_client);
		signal(SIGUSR2, ft_client);
	}
	else
	{
		ft_printf("Error\n");
		return (1);
	}
	return (0);
}
