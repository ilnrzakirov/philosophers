# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/18 10:27:28 by bcarlee           #+#    #+#              #
#    Updated: 2022/01/12 14:20:35 by bcarlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	src/philo.c			src/utils.c			src/error.c\
			src/init.c			src/utils2.c		src/utils3.c\


SRCS_B	= 	\


HEADER	=	includes/philo.h

OBJS	=	$(SRCS:%.c=%.o)

OBJSB	=	$(SRCS_B:%.c=%.o)

CC		=	gcc -g -pthread

INC		=	-I includes 

CFLAGS	=	-I$(HEADER)

$(NAME)	:	$(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

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
