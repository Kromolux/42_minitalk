/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:58:44 by rkaufman          #+#    #+#             */
/*   Updated: 2022/02/10 17:33:43 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_package
{
	int			data;
	int			bit_number;
	pid_t		pid;
}				t_package;

typedef struct s_client
{
	int			signal_received;
	int			pid;
}				t_client;

#endif
