/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarredon <jarredon@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:08:43 by jarredon          #+#    #+#             */
/*   Updated: 2022/05/01 23:18:46 by jarredon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define SIZE 20

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (*str++)
		len++;
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	if (!str)
		return ;
	while (*str)
		write(1, str++, 1);
}

void	ft_putnbr(int n)
{
	long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num < 10)
		ft_putchar((char)(num + '0'));
	else
	{
		ft_putnbr((int)(num / 10));
		ft_putchar((char)(num % 10 + '0'));
	}
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
		num = num * 10 + (*str++ - '0');
	num *= sign;
	if (sign > 0 && num < 0)
		return (-1);
	if (sign < 0 && num > 0)
		return (0);
	return (num);
}
