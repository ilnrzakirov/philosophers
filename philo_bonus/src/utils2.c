/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 12:29:05 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/18 15:04:06 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}

void	ft_putnbr_fd(uint64_t n, int fd)
{
	char	str[13];
	int		length;

	if (n == 0)
		str[0] = '0';
	length = 0;
	while (n != 0)
	{
		str[length++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (length > 0)
		length--;
	while (length >= 0)
		write(fd, &str[length--], 1);
}

int	clear_mate(t_mate *mate)
{
	int		i;
	char	sem[200];

	sem_unlink("sem_fork");
	sem_unlink("sem_write");
	sem_unlink("sem_dead");
	sem_unlink("sem_write_d");
	if (mate->philo)
	{
		i = 0;
		while (i < mate->nbr)
		{
			set_sem_name("Sem_philo", (char *)sem, i);
			sem_unlink(sem);
			set_sem_name("Sem_philo_eat", (char *)sem, i);
			sem_unlink(sem);
			i++;
		}
		free(mate->philo);
	}
	return (1);
}

void	print_msg(t_philo *philo, int i)
{
	sem_wait(philo->mate->write);
	sem_wait(philo->mate->dead);
	ft_putnbr_fd(get_time() - philo->mate->start, 1);
	write(1, " ", 1);
	if (i != 5)
		ft_putnbr_fd(philo->id + 1, 1);
	write(1, get_text(i), ft_strlen(get_text(i)));
	if (i < 4)
		sem_post(philo->mate->dead);
	sem_post(philo->mate->write);
}

void	*counter(void *mate_in)
{
	t_mate	*mate;
	int		res;
	int		i;

	mate = (t_mate *)mate_in;
	res = 0;
	while (res < mate->must_eat)
	{
		i = 0;
		while (i < mate->nbr)
			sem_wait(mate->philo[i++].eat);
		res++;
	}
	print_msg(&mate->philo[0], 5);
	sem_post(mate->lock);
	return ((void *)0);
}
