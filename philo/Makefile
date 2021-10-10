# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jceia <jceia@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 04:53:35 by jceia             #+#    #+#              #
#    Updated: 2021/10/09 21:31:09 by jceia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

INC_DIR		= .

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

FLAG_WARN	= -Wall -Wextra

CFLAGS		=  $(FLAG_WANR) -I$(INC_DIR) -pthread -g
LDFLAGS		= -pthread -g

all:		$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $^ -o $@ $(LDFLAGS)

clean:
			$(RM) -r $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
