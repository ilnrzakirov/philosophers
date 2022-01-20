/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:05:55 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/18 14:43:58 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	init_sem(t_mate *mate)
{
	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	sem_unlink("sem_dead");
	sem_unlink("sem_write_d");
	mate->fork = open_sem("sem_fork", mate->nbr);
	mate->write = open_sem("sem_write", 1);
	mate->lock = open_sem("sem_dead", 0);
	mate->dead = open_sem("sem_write_d", 1);
	if (mate->fork < 0 || mate->write < 0 || mate->lock < 0 || mate->dead < 0)
		return (1);
	return (0);
}

static int	init_philo(t_mate *mate)
{
	int		i;
	char	sem[300];

	i = 0;
	while (i < mate->nbr)
	{
		mate->philo[i].eating = 0;
		mate->philo[i].id = i;
		mate->philo[i].mate = mate;
		set_sem_name("sem_philo", (char *)sem, i);
		sem_unlink(sem);
		mate->philo[i].lock = open_sem(sem, 1);
		if (mate->philo[i].lock < 0)
			return (1);
		set_sem_name("sem_philo_eat", (char *)sem, i);
		sem_unlink(sem);
		mate->philo[i].eat = open_sem(sem, 0);
		if (mate->philo[i].eat < 0)
			return (1);
		i++;
	}
	return (0);
}

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
	mate->fork = NULL;
	mate->philo = NULL;
	mate->philo = malloc(sizeof(*(mate->philo)) * mate->nbr);
	if (!(mate->philo))
		return (1);
	return (1);
}

int	init_mate(t_mate *mate, char **argv, int argc)
{
	if (!(parse_argument(argc, argv, mate)))
		return (1);
	if (mate->nbr < 1 || mate->nbr > 200 || mate->time_die < 0
		|| mate->time_eat < 0 || mate->time_sleep < 0
		|| mate->must_eat < 0)
		return (1);
	if (init_philo(mate))
		return (1);
	if (init_sem(mate))
		return (1);
	return (0);
}
