/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:28:19 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/01 20:28:21 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "utils.h"

static void	send_msg(int pid, char *str)
{
	if (*str == '0')
		kill(pid, SIGUSR1);
	else if (*str == '1')
		kill(pid, SIGUSR2);
	else
		ft_putstr("I don't know what to say\n");
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
