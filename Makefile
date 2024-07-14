NAME = minishell

COMPILER = cc

# FLAGS = -Wall -Wextra -Werror
FLAGS = -g

SRCS = 	src/parsing/minishell.c src/parsing/parser.c src/parsing/input.c src/parsing/tokenizer.c src/parsing/expander.c src/parsing/signals.c \
		src/parsing/ast.c src/parsing/grammar.c \
		src/parsing/deleteme.c #to be deleted

LIBFT = libft/libft.a

OBJS = $(SRCS:.c=.o)

OBJS_BNS = $(SRCS_BNS:.c=.o)

all: $(NAME)

bonus: all

$(NAME): $(OBJS) $(LIBFT)
		$(COMPILER) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lhistory

$(LIBFT):
		$(MAKE) -C libft

.c.o:
	$(COMPILER) -c $(FLAGS) $< -o $@

clean:
		$(MAKE) -C libft clean
		rm -f $(OBJS)

fclean: clean
		rm -f libft/libft.a
		rm -f $(NAME)

re: fclean all