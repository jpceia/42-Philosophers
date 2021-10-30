# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jceia <jceia@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 04:53:35 by jceia             #+#    #+#              #
#    Updated: 2021/10/29 06:16:15 by jceia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo

LIBFT_DIR	= ../libft

INC_DIR		= .

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

FLAG_WARN	= -Wall -Wextra -Werror
FLAG_LIBFT	= -L$(LIBFT_DIR) -lft
FLAG_INC	= -I$(LIBFT_DIR) -I$(INC_DIR)

CFLAGS		= $(FLAG_WARN) $(FLAG_INC) -pthread -g
LDFLAGS		= $(FLAG_LIBFT) -pthread -g

all:		$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(CC) $^ -o $@ $(LDFLAGS)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) -r $(OBJ_DIR)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
