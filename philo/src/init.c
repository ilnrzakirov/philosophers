/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 16:52:26 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/19 15:49:33 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse_argument(int argc, char **argv, t_mate *mate)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!(ft_isdigit_char(argv[i])))
			return (0);
	mate->nbr = ft_atoi(argv[1]);
	mate->time_die = ft_atoi(argv[2]);
	mate->time_eat = ft_atoi(argv[3]);
	mate->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		mate->must_eat = ft_atoi(argv[5]);
	else
		mate->must_eat = 0;
	pthread_mutex_init(&mate->write, NULL);
	pthread_mutex_init(&mate->lock, NULL);
	pthread_mutex_lock(&mate->lock);
	mate->fork = NULL;
	mate->philo = NULL;
	mate->philo = malloc(sizeof(t_philo) * mate->nbr);
	mate->fork = malloc(sizeof(*(mate->fork)) * mate->nbr);
	if (!(mate->philo) || !(mate->fork))
		return (1);
	return (1);
}

int	init_mate(t_mate *mate, char **argv, int argc, int i)
{
	if (!(parse_argument(argc, argv, mate)))
		return (1);
	if (mate->nbr < 1 || mate->nbr > 200 || mate->time_die < 0
		|| mate->time_eat < 0 || mate->time_sleep < 0
		|| mate->must_eat < 0)
		return (1);
	i = 0;
	while (i < mate->nbr)
	{
		mate->philo[i].id = i;
		mate->philo[i].eating = 0;
		mate->philo[i].last_eat = 0;
		mate->philo[i].total_eat = 0;
		mate->philo[i].lfork = i;
		mate->philo[i].rfork = (i + 1) % mate->nbr;
		mate->philo[i].mate = mate;
		pthread_mutex_init(&mate->philo[i].eat, NULL);
		pthread_mutex_init(&mate->fork[i], NULL);
		pthread_mutex_init(&mate->philo[i].lock, NULL);
		pthread_mutex_lock(&mate->philo[i].eat);
		i++;
	}
	return (0);
}
