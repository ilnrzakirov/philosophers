/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 10:38:16 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/17 12:03:35 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(char *str, int i)
{
	if (i == 0)
	{
		write (1, str, ft_strlen(str));
	}
	else if (i == 1)
		write (1, "Bad arguments\n", 14);
	else if (i == 2)
		write (1, "Error creating treads\n", 23);
	else if (i == 3)
		write (1, "Malloc error\n", 13);
	else if (i == 4)
		write (1, "Error gettime\n", 14);
	else if (i == 5)
		write (1, str, ft_strlen(str));
	return (0);
}

int	clear_mate(t_mate *mate)
{
	int	i;

	if (mate->philo)
	{
		i = 0;
		while (i < mate->nbr)
		{
			pthread_mutex_destroy(&mate->philo[i].lock);
			i++;
		}
		free(mate->philo);
		free(mate->fork);
	}
	pthread_mutex_destroy(&mate->write);
	pthread_mutex_destroy(&mate->lock);
	return (1);
}
