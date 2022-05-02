/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:19 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/02 16:25:18 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "utils_bonus.h"

#define DELAY 5000

void	handler(int signal)
{
	(void) signal;
	return ;
}

static void	set_handlers(void)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
}

static void	send_msg(pid_t pid, unsigned char *str)
{
	int	pos;
	int	len;
	int	i;

	len = ft_strlen((char *)str);
	i = -1;
	while (++i <= len)
	{
		pos = -1;
		while (++pos < 8)
		{
			if ((str[i] >> pos) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(DELAY);
		}
	}
}

static void	send_pid(pid_t server_pid)
{
	pid_t	client_pid;
	int		bit;

	client_pid = getpid();
	bit = -1;
	while (++bit < (int) sizeof(client_pid) * 8)
	{
		if ((client_pid >> bit) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(DELAY);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 3)
	{
		ft_putstr("Usage: client <PID> <string>\n");
		exit(EXIT_FAILURE);
	}
	set_handlers();
	pid = ft_atoi(av[1]);
	send_pid(pid);
	send_msg(pid, (unsigned char *)av[2]);
}
