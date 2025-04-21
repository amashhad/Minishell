NAME	= expander.a
CC	= cc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar
ARFLAGS	= rcs
RM	= rm -rf

SRC	=	ft_expander expander_compare expander_fill_utils \
		expander_free ft_expander_utils arrow_expander \

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
