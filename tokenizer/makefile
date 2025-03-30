NAME	= tokenizer.a
CC	= cc
CFLAGS	= -Wall -Wextra -Werror -g
AR	= ar
ARFLAGS	= rcs
RM	= rm -rf

SRC	=	ft_tokenizer tokenizer_utils free_tokens \

SRCS	= $(addsuffix .c, $(SRC))
OBJ_DIR	= obj
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRC:=.o))


all:	$(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
