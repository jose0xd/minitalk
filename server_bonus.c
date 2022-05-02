/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:41 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/02 13:03:54 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"
#include "unicode.h"

static int	g_pid_pos = 0;

static pid_t	get_pid(pid_t pid, int bit)
{
	pid += bit << g_pid_pos++;
	return (pid);
}

static int	make_byte(int bit, unsigned char *byte)
{
	static int	pos = 0;

	*byte += bit << pos++;
	if (pos == 8)
	{
		if (!*byte)
			g_pid_pos = 0;
		*byte = 0;
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
		pid = get_pid(pid, bit);
		return ;
	}
ft_putnbr(g_pid_pos);
ft_putchar('\n');
	if (make_byte(bit, &byte))
		ft_putchar((char)byte);
		/*write(1, &byte, 1);*/
	/*ft_put_uchar(byte);*/
	if (!byte)
		g_pid_pos = 0;
	kill(pid, SIGUSR1);
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
