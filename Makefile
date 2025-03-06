NAME		=	Minishell
CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM		=	rm -rf
SRC		= 	main exit_chk built_in_handle ft_exit_error chg_dir
SRC_DIR		= 	srcs
SRCS		=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:=.o))
LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a


all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
		$(CC) $(OBJS) $(LIBFT) $(CFLAGS) -o $(NAME) -lreadline -L$(LIBFT_PATH) -lft
$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@
$(LIBFT):
		make -C $(LIBFT_PATH) all
clean:
		make -C $(LIBFT_PATH) clean
				$(RM) $(OBJ_DIR)
fclean: clean
		make -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
