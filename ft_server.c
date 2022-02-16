/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:57 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/16 10:02:59 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_received_signal(int signum, siginfo_t *info, void *content);
static void	ft_write_number(long number);

int	main(void)
{
	struct sigaction	sa1;

	sa1.sa_sigaction = &ft_received_signal;
	sa1.sa_flags = SA_SIGINFO | SA_RESTART;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	write(1, "PID=", 4);
	ft_write_number(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}

static void	ft_received_signal(int signum, siginfo_t *info, void *content)
{
	static t_package	package;
	int					bit;

	bit = 0;
	if (signum == SIGUSR2)
		bit = 1;
	package.data = (bit << package.bit_number) | package.data;
	package.bit_number++;
	if (package.bit_number == 8)
	{
		write(1, &package.data, 1);
		package.bit_number = 0;
		package.data = 0;
	}
	kill(info->si_pid, SIGUSR1);
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
