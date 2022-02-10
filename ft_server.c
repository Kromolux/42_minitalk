/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:57 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/10 19:32:21 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_received_signal(int signum, siginfo_t *info, void *content);
static void	ft_write_number(long number);

t_package	g_package;

int	main(void)
{
	struct sigaction	sa1;

	g_package.data = 0;
	g_package.bit_number = 0;
	//sa1.sa_handler = &sig1_handler;
	sa1.sa_sigaction = &ft_received_signal;
	sa1.sa_flags = SA_RESTART;
	//sa2.sa_handler = &sig2_handler;
	//sa2.sa_sigaction = &more_info;
	//sa2.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa1, NULL);
	write(1, "PID=", 4);
	ft_write_number(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
		kill(g_package.pid, SIGUSR1);
	}
	return (0);
}

static void	ft_received_signal(int signum, siginfo_t *info, void *content)
{
	int	bit;

	if (content)
		bit = 0;
	if (signum == SIGUSR1)
	{
		bit = 0;
		write(1, ".", 1);
	}
	else if (signum == SIGUSR2)
	{
		bit = 1;
		write(1, ":", 1);
	}
	g_package.data = (bit << g_package.bit_number) | g_package.data;
	g_package.bit_number++;
	g_package.pid = info->si_pid;
	if (g_package.bit_number == 32)
	{
		write(1, &g_package.data, 1);
		g_package.bit_number = 0;
		g_package.data = 0;
	}
	/*
	printf("\n\nsignal=[%i] content=[%p]\n", signum, content);
	printf("Signal number=[%i]\n", info->si_signo);
	printf("An errno value=[%i]\n", info->si_errno);
	printf("Signal code=[%i]\n", info->si_code);
	//printf("Trap number that caused hardware-generated signal"
    //    "(unused on most architectures)=[%i]\n", info->si_trapno);
	printf("Sending process ID=[%i]\n", info->si_pid);
	printf("Real user ID of sending process=[%i]\n", info->si_uid);
	printf("Exit value or signal=[%i]\n", info->si_status);

	printf("User time consumed=[%li]\n", info->si_utime);
	printf("System time consumed=[%li]\n", info->si_stime);
	printf("POSIX.1b signal=[%i]\n", info->si_int);
	printf("POSIX.1b signal=[%p]\n", info->si_ptr);
	printf("Timer overrun count; POSIX.1b timers=[%i]\n", info->si_overrun);
	printf("Timer ID; POSIX.1b timers=[%i]\n", info->si_timerid);
	printf("Memory location which caused fault=[%p]\n", info->si_addr);
	printf("Band event (was int in glibc 2.3.2 and earlier)=[%lu]\n", info->si_band);
	printf("File descriptor=[%i]\n", info->si_fd);
	printf("Least significant bit of address (since Linux 2.6.32)=[%i]\n", info->si_addr_lsb);
	printf("Lower bound when address violation occurred (since Linux 3.19)=[%p]\n", info->si_lower);
	printf("Upper bound when address violation occurred (since Linux 3.19)=[%p]\n", info->si_upper);
	printf("Protection key on PTE that caused fault (since Linux 4.6)=[%i]\n", info->si_pkey);
	printf("Address of system call instruction (since Linux 3.5)=[%p]\n", info->si_call_addr);
	printf("Number of attempted system call (since Linux 3.5)=[%i]\n", info->si_syscall);
	printf("Architecture of attempted system call (since Linux 3.5)=[%i]\n", info->si_arch);
	*/
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
	c = (char) (number % 10) + '0';
	write(1, &c, 1);
}