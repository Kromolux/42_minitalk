/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:59 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/16 10:02:53 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *nptr);
static void	sig1_handler(int signum, siginfo_t *info, void *content);
static void	ft_send_data(int data, int pid);
static void	ft_write_number(long number);

int	g_signal_received;

int	main(int argc, char **argv)
{
	int					i;
	struct sigaction	sa1;

	if (argc != 3)
	{
		write(1, "program needs 2 arguments! "
			"[server-PID] [string_to_send]\n", 57);
		return (-1);
	}
	i = 0;
	g_signal_received = 1;
	sa1.sa_sigaction = &sig1_handler;
	sa1.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR1, &sa1, NULL);
	write(1, "PID=", 4);
	ft_write_number(getpid());
	write(1, "\n", 1);
	while (argv[2][i])
	{
		ft_send_data(argv[2][i], ft_atoi(argv[1]));
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
		usleep(5000);
	}
}

static void	sig1_handler(int signum, siginfo_t *info, void *content)
{
	g_signal_received = 1;
	return ;
	(void)signum;
	(void)info;
	(void)content;
}

static void	ft_write_number(long number)
{
	char	c;

	if (number < 0)
	{
		number *= -1;
		write(1, "-", 1);
	}
	if (number > 9)
		ft_write_number(number / 10);
	c = (char)(number % 10) + '0';
	write(1, &c, 1);
}
