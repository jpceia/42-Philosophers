# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jceia <jceia@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/30 04:53:35 by jceia             #+#    #+#              #
#    Updated: 2021/09/26 02:15:00 by jceia            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFTDIR	= ./libft
LIBFT		= $(LIBFTDIR)/libft.a

INC_DIR		= .

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(shell find $(SRC_DIR) -name *.c -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

NAME		= philosophers

CFLAGS		= -Wall -Wextra -pthread -I$(INC_DIR) -I$(LIBFTDIR)

all:		$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
			$(MAKE) -C $(LIBFTDIR)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $^ -o $@

clean:
			$(MAKE) -C $(LIBFTDIR) clean
			$(RM) -r $(OBJDIR)

fclean:		clean
			$(MAKE) -C $(LIBFTDIR) fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
