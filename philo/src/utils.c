/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:40:32 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/17 12:08:50 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long long	get_time(void)
{
	static struct timeval		tv;
	unsigned long long			res;

	gettimeofday(&tv, NULL);
	res = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (res);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	return (-1);
}

int	ft_atoi(char *s)
{
	int						i;
	int						si;
	unsigned long long int	result;

	i = 0;
	si = 1;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			si = -1;
	}
	result = 0;
	while (s[i] >= '0' && s[i] <= '9' )
		result = (result * 10) + (s[i++] - '0');
	if (i > 19)
	{
		if (si < 0)
			return (0);
		return (-1);
	}
	return (result * si);
}

int	ft_isdigit_char(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((ft_isdigit(str[i])) == -1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}
