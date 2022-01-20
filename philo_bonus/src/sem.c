/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:27:31 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/18 12:41:57 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

char	*set_sem_name(char *str, char *buf, int id)
{
	int	i;

	i = ft_strcpy(buf, str);
	while (id > 0)
	{
		buf[i++] = (id % 10) + '0';
		id = id / 10;
	}
	buf[i] = '\0';
	return (buf);
}

sem_t	*open_sem(char *name, int value)
{
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}
