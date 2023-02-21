/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnakajo <tnakajo@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:10:59 by tnakajo           #+#    #+#             */
/*   Updated: 2023/02/21 23:34:44 by tnakajo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_client(int signal)
{
	static int	i;

	if (signal == SIGUSR2)
		i++;
	// else
	// 	ft_printf("★ Total Length from Server : %d\n", i);
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
		if (c < 0)
			ui++;
	}
	if (c == 3 && end == 1)
		// ft_printf("★ Total Length with Unicode: %i\n", i);
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
	if (argc == 3 && argv[2][0])
	{
		pid = ft_atoi(argv[1]);
		// ft_printf("☆ Message You Will send    : \"%s\"\n", argv[2]);
		// ft_printf("☆ The Length You Will send : %i\n", ft_strlen(argv[2]));
		while (argv[2][i] != '\0')
		{
			if (argv[2][i] == '\\' && argv[2][i + 1] == 'n')
			{
				i++;
				argv[2][i] = '\n';
			}
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

/*

  File "/nfs/homes/tnakajo/francinette/testers/BaseTester.py", line 183, in test_using
    return (tester.name, tx.execute())
  File "/nfs/homes/tnakajo/francinette/testers/minitalk/Fsoares.py", line 77, in execute
    result = self.test_client_server()
  File "/nfs/homes/tnakajo/francinette/testers/minitalk/Fsoares.py", line 96, in test_client_server
    no_leaks = self.test_leaks()
  File "/nfs/homes/tnakajo/francinette/testers/minitalk/Fsoares.py", line 243, in test_leaks
    self.send_message(server, "teste\n-----\n")
  File "/nfs/homes/tnakajo/francinette/testers/minitalk/Fsoares.py", line 275, in send_message
    return re.match(r"__PID: (\d+)", client.stdout.decode('utf-8', errors="backslashreplace")).group(1)

*/