# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jceia <jceia@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 04:53:35 by jceia             #+#    #+#              #
#    Updated: 2021/10/30 19:27:58 by jceia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

LIBFT_DIR	= ../libft

INC_DIR		= .

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

FLAGS_WARN	= -Wall -Wextra -Werror
FLAGS_DEBUG	= -g -fsanitize=address
FLAGS_OPT	= -O3
FLAGS_LIBFT	= -L$(LIBFT_DIR) -lft
FLAGS_INC	= -I$(LIBFT_DIR) -I$(INC_DIR)

CFLAGS		= $(FLAGS_WANR) $(FLAGS_OPT) $(FLAGS_INC)
LDFLAGS		= $(FLAGS_LIBFT) $(FLAGS_OPT) -pthread

all:		$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) -c $< -o $@ $(CFLAGS) 

$(NAME):	$(OBJS)
			$(MAKE) -C $(LIBFT_DIR)
			$(CC)   $^ -o $@ $(LDFLAGS)

clean:
			$(MAKE) -C $(LIBFT_DIR) clean
			$(RM) -r $(OBJ_DIR)

fclean:		clean
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

# Debbugging functions

debug:		CFLAGS += $(FLAGS_DEBUG)
debug:		LDFLAGS += $(FLAGS_DEBUG)
debug:		re

# Phony

.PHONY:		all clean fclean re
