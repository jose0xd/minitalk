/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:19 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/01 23:39:45 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "utils.h"

#define DELAY 5000

static void	send_msg(int pid, char *str)
{
	int	pos;
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (++i <= len)
	{
		pos = -1;
		while (++pos < 7)
		{
			if ((str[i] >> pos) & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(DELAY);
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_putstr("Usage: client <PID> <string>\n");
		exit(EXIT_FAILURE);
	}
	send_msg(ft_atoi(av[1]), av[2]);
}
