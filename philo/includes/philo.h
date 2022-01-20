/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:38:10 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/13 11:30:45 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>

struct	s_mate;
typedef struct s_philo
{
	unsigned long long	last_eat;
	int					id;
	int					total_eat;
	int					lfork;
	int					eating;
	int					rfork;
	unsigned long long	limit;
	pthread_mutex_t		lock;
	pthread_mutex_t		eat;
	struct s_mate		*mate;
}						t_philo;

typedef struct s_mate
{
	pthread_mutex_t		write;
	pthread_mutex_t		lock;
	t_philo				*philo;
	unsigned long long	start;
	int					nbr;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	char				state;
	pthread_mutex_t		*fork;
}						t_mate;

int					print_error(char *str, int i);
int					ft_strlen(const char *str);
int					init_mate(t_mate *mate, char **argv, int argc, int i);
int					ft_isdigit_char(char *str);
int					ft_atoi(char *str);
unsigned long long	get_time(void);
int					clear_mate(t_mate *mate);
void				ft_putnbr_fd(int nb, int fd);
void				print_msg(t_philo *philo, int i);
char				*get_text(int i);
void				eat(t_philo *philo);
void				free_forks(t_philo *philo);
void				take_forks(t_philo *philo);
#endif