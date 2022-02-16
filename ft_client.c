/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:59 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/16 19:03:14 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_server_confirmed_bit(int signum, siginfo_t *info, void *content);
static void	ft_send_data(int data, int pid);
static void	ft_error_handling(int argc, char **argv);

int	g_signal_received;

int	main(int argc, char **argv)
{
	int					i;
	int					pid;
	struct sigaction	sa1;

	ft_error_handling(argc, argv);
	i = 0;
	g_signal_received = 1;
	sa1.sa_sigaction = &ft_server_confirmed_bit;
	sa1.sa_flags = SA_SIGINFO;
	sigemptyset(&sa1.sa_mask);
	sigaction(SIGUSR1, &sa1, NULL);
	pid = ft_atoi(argv[1]);
	while (argv[2][i])
	{
		ft_send_data(argv[2][i], pid);
		i++;
	}
	write(1, "Message send sucessfully!\n", 26);
	return (0);
}

void	ft_error_handling(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "program needs 2 arguments! "
			"[server-PID] [string_to_send]\n", 57);
		exit (-1);
	}
	if (kill(ft_atoi(argv[1]), 0) == -1)
	{
		write(1, "invalid server pid!\n", 20);
		exit (-1);
	}
}

static void	ft_send_data(int data, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (g_signal_received == 1)
		{
			g_signal_received = 0;
			if (((data >> i) & 1) == 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			i++;
		}
		usleep(100000);
	}
}

static void	ft_server_confirmed_bit(int signum, siginfo_t *info, void *content)
{
	g_signal_received = 1;
	return ;
	(void)signum;
	(void)info;
	(void)content;
}
