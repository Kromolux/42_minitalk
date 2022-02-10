/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:59 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/10 19:35:56 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *nptr);
static void	sig1_handler(int signum, siginfo_t *info, void *content);
static void	ft_send_data(int data);

t_client	g_client;

int	main(int argc, char **argv)
{
	int i;
	struct sigaction	sa1;

	if (argc != 3)
	{
		write(1, "program needs 2 arguments! [server-PID] [string_to_send]\n", 57);
		return (-1);
	}
	i = 0;
	g_client.signal_received = 1;
	//sa1.sa_handler = &sig2_handler;
	sa1.sa_sigaction = &sig1_handler;
	sa1.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa1, NULL);
	//sigaction(SIGUSR2, &sa2, NULL);
	g_client.pid = ft_atoi(argv[1]);
	while (argv[2][i])
	{
		ft_send_data(argv[2][i]);
		i++;
	}
	write(1, "Message send sucessfully!\n", 26);
	return (0);
}

static int	ft_atoi(const char *nptr)
{
	int	output;
	int	i;

	i = 0;
	output = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output *= 10;
		output += nptr[i] - '0';
		i++;
	}
	return (output);
}

static void	ft_send_data(int data)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		//if (g_client.signal_received == 1)
		//{
			if (((data >> i) & 1) == 1)
				kill(g_client.pid, SIGUSR2);
			else
				kill(g_client.pid, SIGUSR1);
			g_client.signal_received = 0;
			i++;
		//}
	usleep(500);
	}
}

static void	sig1_handler(int signum, siginfo_t *info, void *content)
{
	//if (info->si_pid == g_client.pid)
	write(1, "^", 1);
	g_client.signal_received = 1;
	return ;
	if (signum == SIGUSR1 || info->si_pid == g_client.pid || content)
		return ;
}
