/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:57 by rkaufman          #+#    #+#             */
/*   Updated: 2022/01/25 21:15:18 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
void	sig_handler(int signum);

int	main(void)
{
	signal(SIGINT, sig_handler);
	printf("PID=[%i]\n", getpid());
	printf("SIGUSR1=%i SIGUSR2=%i\n", SIGUSR1, SIGUSR2);
	pause();
	return (0);
}

void	sig_handler(int signum)
{
	printf("got a signal! %i\n", signum);
}
