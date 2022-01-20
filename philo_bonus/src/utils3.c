/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:02:10 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/18 14:56:52 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

void	take_forks(t_philo *philo)
{
	sem_wait(philo->mate->fork);
	print_msg(philo, 2);
	sem_wait(philo->mate->fork);
	print_msg(philo, 2);
}

void	free_forks(t_philo *philo)
{
	print_msg(philo, 1);
	sem_post(philo->mate->fork);
	sem_post(philo->mate->fork);
	usleep(philo->mate->time_sleep * 1000);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->lock);
	philo->eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->mate->time_die;
	print_msg(philo, 0);
	usleep(philo->mate->time_eat * 1000);
	philo->total_eat++;
	philo->eating = 0;
	sem_post(philo->lock);
	sem_post(philo->eat);
}
