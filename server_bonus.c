/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:41 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/02 01:31:13 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"

static int	g_pid_pos = 0;

static pid_t	get_pid(pid_t pid, int bit)
{
	pid += bit << g_pid_pos++;
	return (pid);
}

static int	make_char(int bit)
{
	static char	c = 0;
	static int	pos = 0;
	int			end;

	end = 0;
	c += bit << pos++;
	if (pos == 7)
	{
		if (!c)
		{
			c = '\n';
			g_pid_pos = 0;
			end = 1;
		}
		ft_putchar(c);
		c = 0;
		pos = 0;
	}
	return (end);
}

static void	handler(int signal)
{
	int				bit;
	static pid_t	pid = 0;
	int				end;

	if (signal == SIGUSR1)
		bit = 0;
	else if (signal == SIGUSR2)
		bit = 1;
	else
		exit(EXIT_FAILURE);
	if (g_pid_pos < (int) sizeof(pid) * 8)
	{
		pid = get_pid(pid, bit);
		return ;
	}
	end = make_char(bit);
	kill(pid, SIGUSR1);
	if (end)
		pid = 0;
}

static void	set_handlers(void)
{
	struct sigaction	act;

	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{
	set_handlers();
	ft_putstr("Server running: PID: ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	while (42)
		pause();
}
