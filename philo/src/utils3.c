/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:20:03 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/13 11:11:59 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_msg(t_philo *philo, int i)
{
	static int	j;

	pthread_mutex_lock(&philo->mate->write);
	if (!j)
	{
		ft_putnbr_fd(get_time() - philo->mate->start, 1);
		write(1, " ", 1);
		if (i != 5)
			ft_putnbr_fd(philo->id + 1, 1);
		if (i >= 4)
			j = 1;
		write (1, get_text(i), ft_strlen(get_text(i)));
	}
	pthread_mutex_unlock(&philo->mate->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->mate->fork[philo->lfork]);
	print_msg(philo, 2);
	pthread_mutex_lock(&philo->mate->fork[philo->rfork]);
	print_msg(philo, 2);
}

void	free_forks(t_philo *philo)
{
	print_msg(philo, 1);
	pthread_mutex_unlock(&philo->mate->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->mate->fork[philo->rfork]);
	usleep(philo->mate->time_sleep * 1000);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->mate->time_die;
	print_msg(philo, 0);
	usleep(philo->mate->time_eat * 1000);
	philo->total_eat++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->eat);
}
