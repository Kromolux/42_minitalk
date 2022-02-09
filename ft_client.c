/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:59 by rkaufman          #+#    #+#             */
/*   Updated: 2022/01/29 20:40:08 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
static int	ft_atoi(const char *nptr);
void	sig1_handler(int signum, siginfo_t *info, void *content);
void	ft_send_data(int pid, int data);

int	g_received;

int	main(int argc, char **argv)
{
	int	pid;
	struct sigaction	sa1;
	struct sigaction	sa2;

	g_received = 1;
	sa1.sa_sigaction = &sig1_handler;
	sa1.sa_flags = SA_RESTART;
	sa2.sa_sigaction &sig1_handler;
	sa2.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	if (argc != 3)
		return (-1);
	pid = ft_atoi(argv[1]);
	//sigaction(SIGUSR1, &sa1, NULL);
	printf("PID=[%i]\n", getpid());
	//kill(pid, SIGUSR2);
	printf("[%s][%s]\n", argv[1], argv[2]);
	ft_send_data(pid, argv[2][0]);
	pause();
	//usleep(50);
	//kill(pid, SIGUSR1);

	//kill(pid, SIGUSR1);

	//write(1, "\u00A9\n", 3);
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

void	ft_send_data(int pid, int data)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (g_received == 1)
		{
			if (((data >> i) & 1) == 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			g_received = 0;
			i++;
		}
	}
}

void	sig1_handler(int signum, siginfo_t *info, void *content)
{
	printf("received feedback=[%i] from pid=[%i] [%p]\n", signum, info->si_pid, content);
	g_received = 1;
}

void	ft_write_int_in_bits(int data)
{
	int	i;
	char	c;

	i = 0;
	while (i < 32)
	{
		c = (char) (((data >> i) & 1) + '0');
		write(1, &c, 1);
		i++;
	}
}