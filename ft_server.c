/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:57 by rkaufman          #+#    #+#             */
/*   Updated: 2022/01/29 20:34:41 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
void	sig1_handler(int signum);
void	sig2_handler(int signum);
void	more_info(int signum, siginfo_t *info, void *content);

typedef struct s_package
{
	int			data;
	int			bit_number;
} 				t_package;

t_package	g_package;


int	main(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	g_package.data = 0;
	g_package.bit_number = 0;
	sa1.sa_handler = &sig1_handler;
	sa1.sa_sigaction = &more_info;
	sa1.sa_flags = SA_RESTART;
	sa2.sa_handler = &sig2_handler;
	sa2.sa_sigaction = &more_info;
	sa2.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa1, NULL);
	sigaction(SIGUSR2, &sa2, NULL);
	//signal(SIGUSR1, sig1_handler);
	printf("PID=[%i]\n", getpid());
	printf("SIGUSR1=%i SIGUSR2=%i\n", SIGUSR1, SIGUSR2);
	while (1);
	return (0);
}

void	sig1_handler(int signum)
{
	printf("\ngot a 1 signal! %i\n", signum);
}


void	sig2_handler(int signum)
{
	printf("\ngot a 2 signal! %i\n", signum);
}

void	more_info(int signum, siginfo_t *info, void *content)
{
	int	bit;

	if (content)
		bit = 0;
	//bit = (int) content;
	if (signum == SIGUSR1)
		bit = 0;
	else if (signum == SIGUSR2)
		bit = 1;
	g_package.data = (bit << g_package.bit_number) | g_package.data;
	g_package.bit_number++;
	if (g_package.bit_number == 32)
	{
		write(1, &g_package.data, 4);
		g_package.bit_number = 0;
		g_package.data = 0;
	}
	kill(info->si_pid, SIGUSR1);
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