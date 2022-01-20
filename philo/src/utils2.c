/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:57:39 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/12 15:09:40 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_degree(int n)
{
	int	deg;

	deg = 0;
	while (n > 9)
	{
		n = n / 10;
		deg++;
	}
	return (deg);
}

void	ft_print(char sym, int fd)
{
	write (fd, &sym, 1);
}

int	ft_square(int degree)
{
	int	result;

	result = 1;
	while (degree != 0)
	{
		result = result * 10;
		degree--;
	}
	return (result);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int	degree;
	int	temp;

	if (nb == -2147483648)
	{
		ft_print('-', fd);
		ft_print('2', fd);
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_print('-', fd);
		nb = -nb;
	}
	degree = ft_degree(nb);
	while (degree >= 0)
	{
		temp = nb / ft_square(degree);
		ft_print('0' + temp, fd);
		nb = nb % ft_square(degree);
		degree--;
	}
}

char	*get_text(int i)
{
	if (i == 0)
		return (" is eating\n");
	else if (i == 1)
		return (" is sleeping\n");
	else if (i == 2)
		return (" has taken a fork\n");
	else if (i == 3)
		return (" is thinking\n");
	else if (i == 5)
		return ("must eat count reached\n");
	return (" died\n");
}
