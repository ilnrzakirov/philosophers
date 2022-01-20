/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 16:38:10 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/18 14:49:44 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_mate;
typedef struct s_philo
{
	unsigned long long	last_eat;
	int					id;
	pid_t				pid;
	int					total_eat;
	int					eating;
	unsigned long long	limit;
	sem_t				*lock;
	sem_t				*eat;
	struct s_mate		*mate;
}						t_philo;

typedef struct s_mate
{
	sem_t				*write;
	sem_t				*lock;
	t_philo				*philo;
	unsigned long long	start;
	int					nbr;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					must_eat;
	char				state;
	sem_t				*fork;
	sem_t				*dead;
}						t_mate;

int					ft_strlen(const char *str);
int					print_error(char *str, int i);
int					init_mate(t_mate *mate, char **argv, int argc);
int					ft_isdigit_char(char *str);
int					ft_atoi(char *s);
unsigned long long	get_time(void);
int					ft_strcpy(char *dst, const char *src);
void				ft_putnbr_fd(uint64_t n, int fd);
char				*set_sem_name(char *str, char *buf, int id);
sem_t				*open_sem(char *name, int value);
char				*get_text(int i);
void				*counter(void *mate_in);
void				print_msg(t_philo *philo, int i);
int					clear_mate(t_mate *mate);
void				take_forks(t_philo *philo);
void				free_forks(t_philo *philo);
void				eat(t_philo *philo);
#endif