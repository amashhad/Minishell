NAME		=	minishell
CC		=	cc
CFLAGS		=	-Wall -Wextra -Werror -g
RM		=	rm -rf
SRC		= 	main exit_chk ft_exit_error signal \
			ft_engine_start $(EXECUTER_SRCS) $(TOKENIZER_SRCS) $(BUILTIN_SRCS)\

SRC_DIR		= 	srcs
SRCS		=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC))) \
				$(addprefix $(EXECUTER_DIR)/, $(addsuffix .c, $(EXECUTER_SRCS)))\
				$(addprefix $(EXPANDER_DIR)/, $(addsuffix .c, $(EXPANDER_SRCS)))\
				$(addprefix $(TOKENIZER_DIR)/, $(addsuffix .c, $(TOKENIZER_SRCS)))\
				$(addprefix $(BUILTIN_DIR)/, $(addsuffix .c, $(BUILTIN_SRCS)))\

EXECUTER_DIR	=	executer
EXECUTER_SRCS	=	minishell_execute execution_err_handle execution_utils \
					pipe_exeution cmd_operations free_execution\

EXPANDER_DIR	=	expander
EXPANDER_SRCS	=	ft_expander expander_compare expander_fill_utils \
					expander_free ft_expander_utils arrow_expander \

TOKENIZER_DIR	=	tokenizer
TOKENIZER_SRCS	=	ft_tokenizer tokenizer_utils free_tokens \

BUILTIN_DIR		=	builtin
BUILTIN_SRCS	=	builtin chdir echo env \
					export unset\

OBJ_DIR		=	obj
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC:=.o)) \
				$(addprefix $(OBJ_DIR)/, $(EXECUTER_SRCS:=.o))\
				$(addprefix $(OBJ_DIR)/, $(EXPANDER_SRCS:=.o))\
				$(addprefix $(OBJ_DIR)/, $(TOKENIZER_SRCS:=.o))\
				$(addprefix $(OBJ_DIR)/, $(BUILTIN_SRCS:=.o))\

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

LDFLAGS = -L$(LIBFT_PATH)

all:	$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
		$(CC) $(CFLAGS)  $(^)  -o $(@) -lreadline $(LDFLAGS)

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXECUTER_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(EXPANDER_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c | $(OBJ_DIR)
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
