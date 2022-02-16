/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:57 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/16 19:03:02 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_received_signal(int signum, siginfo_t *info, void *content);

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &ft_received_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	write(1, "PID=", 4);
	ft_write_number(getpid());
	write(1, "\n", 1);
	while (1)
		usleep(1);
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
