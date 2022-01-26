/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:56:59 by rkaufman          #+#    #+#             */
/*   Updated: 2022/01/26 12:55:19 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <stdio.h>
static int	ft_atoi(const char *nptr);

int	main(int argc, char **argv)
{
	int	pid;
	if (argc != 2)
		return (-1);
	pid = ft_atoi(argv[1]);
	printf("PID=[%i]\n", getpid());
	kill(pid, SIGUSR1);
	sleep(1);
	kill(pid, SIGUSR2);
	//kill(pid, SIGUSR1);
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
