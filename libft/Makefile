NAME		= libft.a

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		:= $(shell find $(SRC_DIR) -name "*.c" -type f)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -I.

all:		$(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			ar rc $@ $(OBJS)

clean:
			$(RM) -rf $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
