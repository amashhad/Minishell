NAME		=	Minishell
CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM		=	rm -rf
SRC		= 	main exit_chk built_in_handle ft_exit_error \
			chg_dir export_unset echo expander 
SRC_DIR		= 	srcs
SRCS		=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))

OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:=.o))

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

TOKENIZER_PATH	=	./tokenizer
TOKENIZER	=	$(TOKENIZER_PATH)/tokenizer.a

LDFLAGS = -L$(LIBFT_PATH) -L$(TOKENIZER_PATH)


all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(TOKENIZER)
		$(CC) $(CFLAGS)  $(^)  -o $(@) -lreadline $(LDFLAGS)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@
$(LIBFT):
		make -C $(LIBFT_PATH) all
$(TOKENIZER):
		make -C $(TOKENIZER_PATH)
clean:
		make -C $(LIBFT_PATH) clean
		make -C  $(TOKENIZER_PATH) clean		
		$(RM) $(OBJ_DIR)
fclean: clean
		make -C $(LIBFT_PATH) fclean
		make -C  $(TOKENIZER_PATH) fclean
		$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
