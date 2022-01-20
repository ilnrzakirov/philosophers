/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:25:16 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/19 10:33:00 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*control_dead(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->lock);
		if (!philo->eating && get_time() > philo->limit)
		{
			print_msg(philo, 4);
			sem_post(philo->lock);
			sem_post(philo->mate->lock);
			return ((void *)0);
		}
		sem_post(philo->lock);
		usleep(1000);
	}
	return ((void *)0);
}

int	run_dinner(t_philo *arg)
{
	t_philo		*philo;
	pthread_t	tr;

	philo = (t_philo *)arg;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->mate->time_die;
	if (pthread_create(&tr, NULL, &control_dead, philo))
		return (1);
	pthread_detach(tr);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		free_forks(philo);
		print_msg(philo, 3);
	}
	return (0);
}

int	init_process(t_mate *mate)
{
	int		i;

	mate->start = get_time();
	i = 0;
	while (i < mate->nbr)
	{
		mate->philo[i].pid = fork();
		if (mate->philo[i].pid < 0)
			return (1);
		else if (!mate->philo[i].pid)
		{
			run_dinner(&mate->philo[i]);
			exit (0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int	control_thread(t_mate *mate)
{
	pthread_t	tr;

	if (mate->must_eat > 0)
	{
		if (pthread_create(&tr, NULL, &counter, (void *)mate))
			return (1);
		pthread_detach(tr);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_mate	mate;

	if (argc < 5 || argc > 6)
		return (print_error("Bad arguments\n", 0));
	if (init_mate(&mate, argv, argc))
		return (print_error("Bad argument\n", 0) && clear_mate(&mate));
	if (mate.must_eat > 0)
		if (control_thread(&mate))
			return (print_error("Bad argument\n", 0) && clear_mate(&mate));
	if (init_process(&mate))
		return (print_error("Bad argument\n", 0) && clear_mate(&mate));
	sem_wait(mate.lock);
	i = 0;
	while (i < mate.nbr)
	{
		kill(mate.philo[i].pid, SIGKILL);
		i++;
	}
	clear_mate(&mate);
	return (0);
}
