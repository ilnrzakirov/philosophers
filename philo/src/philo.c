/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:39:10 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/19 15:42:38 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*control(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->lock);
		if (!philo->eating && get_time() > philo->limit)
		{
			print_msg(philo, 4);
			pthread_mutex_unlock(&philo->lock);
			pthread_mutex_unlock(&philo->mate->lock);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->lock);
		usleep(1000);
	}
}

void	*run_dinner(void *arg)
{
	t_philo		*philo;
	pthread_t	tr;

	philo = (t_philo *)arg;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->mate->time_die;
	if (pthread_create(&tr, NULL, &control, arg))
		return ((void *)1);
	pthread_detach(tr);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		free_forks(philo);
		print_msg(philo, 3);
	}
}

void	*must_eat_msg(void *mate_in)
{
	t_mate	*mate;
	int		i;
	int		res;

	mate = (t_mate *)mate_in;
	res = 0;
	while (res < mate->must_eat)
	{
		i = 0;
		while (i < mate->nbr)
			pthread_mutex_lock(&mate->philo[i++].eat);
		res++;
	}
	print_msg(&mate->philo[0], 5);
	pthread_mutex_unlock(&mate->lock);
	return ((void *)0);
}

int	init_threads(t_mate *mate)
{
	int			i;
	pthread_t	tr;
	void		*r;

	mate->start = get_time();
	if (mate->must_eat > 0)
	{
		if (pthread_create(&tr, NULL, &must_eat_msg, (void *)mate))
			return (1);
		pthread_detach(tr);
	}
	i = 0;
	while (i < mate->nbr)
	{
		r = (void *)(&mate->philo[i]);
		if (pthread_create(&tr, NULL, &run_dinner, r))
			return (1);
		pthread_detach(tr);
		usleep(100);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mate	mate;
	int		i;

	if (argc < 5 || argc > 6)
		print_error("bad arguments\n", 0);
	i = init_mate(&mate, argv, argc, 0);
	if (i > 0)
	{
		if (i > 1)
			clear_mate(&mate);
		print_error("bad arguments\n", i);
		return (1);
	}
	if (init_threads(&mate))
		return (print_error("Pthread error\n", 5) + clear_mate(&mate));
	pthread_mutex_lock(&mate.lock);
	pthread_mutex_unlock(&mate.lock);
	clear_mate(&mate);
	return (0);
}
