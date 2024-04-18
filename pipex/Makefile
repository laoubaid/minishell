NAME = pipex

NAMEB = pipex_bonus

SRCS = ./mandatory/ft_split.c  ./mandatory/ft_strjoin.c ./mandatory/pipex.c \
		./mandatory/splitpath.c ./mandatory/path.c ./mandatory/main.c \
		./mandatory/pipex_utils.c

SRCB = ./bonus/ft_split_bonus.c  ./bonus/ft_strjoin_bonus.c ./bonus/pipex_bonus.c \
		./bonus/main_bonus.c ./bonus/splitpath_bonus.c ./bonus/path_bonus.c \
		./bonus/pipex_utils_bonus.c ./bonus/get_next_line_utils_bonus.c \
		./bonus/get_next_line_bonus.c

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRCS:.c=.o)
OBJB = $(SRCB:.c=.o)

all : $(NAME)

bonus : $(NAMEB)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(NAMEB): $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $@

clean:
	@rm -f $(OBJS) $(OBJB) 
fclean: clean
	@rm -f $(NAME) $(NAMEB)
re: fclean all