/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:41 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/02 16:42:14 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "utils_bonus.h"
#include "unicode_bonus.h"

static int	g_pid_pos = 0;

static int	make_uchar(int bit, unsigned char *byte)
{
	static int	pos = 0;

	if (pos == 0)
		*byte = 0;
	*byte += bit << pos++;
	if (pos == 8)
	{
		if (!*byte)
		{
			*byte = '\n';
			g_pid_pos = 0;
		}
		pos = 0;
		return (1);
	}
	return (0);
}

static void	handler(int signal)
{
	int						bit;
	static pid_t			pid = 0;
	static unsigned char	byte = 0;

	if (signal == SIGUSR1)
		bit = 0;
	else if (signal == SIGUSR2)
		bit = 1;
	else
		exit(EXIT_FAILURE);
	if (g_pid_pos < (int) sizeof(pid) * 8)
	{
		pid += bit << g_pid_pos++;
		return ;
	}
	if (make_uchar(bit, &byte))
		ft_put_uchar(byte);
	kill(pid, SIGUSR1);
	if (g_pid_pos == 0)
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
