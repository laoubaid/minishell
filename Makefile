NAME = minishell

COMPILER = cc

# FLAGS = -Wall -Wextra -Werror
# FLAGS = -g3
FLAGS = -fsanitize=address -g3

SRCS = 	src/minishell.c src/parsing/parser.c src/parsing/tokenizer.c src/parsing/expander.c src/parsing/signals.c \
		src/parsing/ast.c src/parsing/grammar.c src/parsing/expand_no_quote.c src/parsing/expand_str.c src/parsing/expand_key.c \
		src/parsing/utils.c src/parsing/token_utils.c src/parsing/ast_cmd.c src/parsing/ast_utils1.c src/parsing/ast_utils2.c \
		src/parsing/expand_wildcard.c src/parsing/expand_redir.c \
		src/execution/executer.c src/execution/path.c src/execution/split.c src/execution/redirecte.c src/execution/errors.c \
		src/execution/pipe.c src/execution/environment.c src/execution/builtins.c src/execution/utils.c \
		src/execution/builtins_suite.c src/execution/environment_suite.c src/execution/heredoc.c src/execution/execution.c \
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
	$(COMPILER) -I./include/ -c $(FLAGS) $< -o $@

clean:
		$(MAKE) -C libft clean
		rm -f $(OBJS)

fclean: clean
		rm -f libft/libft.a
		rm -f $(NAME)

re: fclean all
