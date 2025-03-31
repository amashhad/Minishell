NAME		=	minishell
CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM		=	rm -rf
SRC		= 	main exit_chk ft_exit_error \
			ft_engine_start $(BUILTIN_SRCS)\

SRC_DIR		= 	srcs
SRCS		=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC))) \
				$(addprefix $(BUILTIN_DIR)/, $(addsuffix .c, $(BUILTIN_SRCS)))

BUILTIN_DIR	=	builtin
BUILTIN_SRCS	=	builtin chdir echo env \
					export unset

OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:=.o)) \
				$(addprefix $(OBJ_DIR)/, $(BUILTIN_SRCS:=.o))

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

TOKENIZER_PATH	=	./tokenizer
TOKENIZER	=	$(TOKENIZER_PATH)/tokenizer.a

EXPANDER_PATH	=	./expander
EXPANDER	=	$(EXPANDER_PATH)/expander.a

LDFLAGS = -L$(LIBFT_PATH) -L$(TOKENIZER_PATH) -L$(EXPANDER_PATH)

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(TOKENIZER) $(EXPANDER)
		$(CC) $(CFLAGS)  $(^)  -o $(@) -lreadline $(LDFLAGS)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		make -C $(LIBFT_PATH) all
$(TOKENIZER):
		make -C $(TOKENIZER_PATH) all
$(EXPANDER):
		make -C $(EXPANDER_PATH) all
clean:
		make -C $(LIBFT_PATH) clean
		make -C  $(TOKENIZER_PATH) clean
		make -C  $(EXPANDER_PATH) clean
		$(RM) $(OBJ_DIR)
fclean: clean
		make -C $(LIBFT_PATH) fclean
		make -C  $(TOKENIZER_PATH) fclean
		make -C  $(EXPANDER_PATH) fclean
		$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
