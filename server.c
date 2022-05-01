/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:41 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/01 23:38:20 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "utils.h"

static void	handler(int signal)
{
	static char	c = 0;
	static int	pos = 0;
	int			bit;

	if (signal == SIGUSR1)
		bit = 0;
	else if (signal == SIGUSR2)
		bit = 1;
	else
		exit(EXIT_FAILURE);
	c += bit << pos++;
	if (pos == 7)
	{
		if (!c)
			c = '\n';
		ft_putchar(c);
		c = 0;
		pos = 0;
	}
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
