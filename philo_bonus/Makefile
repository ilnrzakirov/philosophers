# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 10:27:28 by bcarlee           #+#    #+#              #
#    Updated: 2022/01/18 14:30:15 by bcarlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

SRCS	=	src/philo_bonus.c			src/utils.c			src/error.c\
			src/init.c					src/sem.c			src/utils2.c\
			src/utils3.c


SRCS_B	= 	\


HEADER	=	includes/philo_bonus.h

OBJS	=	$(SRCS:%.c=%.o)

OBJSB	=	$(SRCS_B:%.c=%.o)

CC		=	gcc -g -pthread

INC		=	-I includes 

CFLAGS	=	-Wall -Wextra -Werror -I$(HEADER)

$(NAME)	:	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)
	@rm -f $(OBJS) $(OBJSB)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY	:	all clean fclean re

all		:	$(NAME)

bonus	:	$(OBJSB) $(HEADER)
	$(CC) $(CFLAGS) $(INC) $(OBJSB) -o $(NAME)
	
	
clean	:
	@rm -f $(OBJS) $(OBJSB)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all
