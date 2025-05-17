NAME = minishell

CC = cc

CFLAGS = -g #-Wall -Wextra -Werror 

#delete t.c
SRC = minishell.c list_utils.c check_input.c exec.c t.c mini_split.c free.c heredoc.c env_var.c check_commands.c free_all.c check_files.c testing.c parse_input.c var_utils.c quotes.c exp_exit.c
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_MAKEFILE = $(LIBFT_DIR)/Makefile

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
