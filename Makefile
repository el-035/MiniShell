NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror 

SRC = minishell.c list_utils.c syntax.c syntax_utils.c  mini_split.c \
	free.c heredoc.c env_var.c check_commands.c free_all.c  \
	parse_input.c var_utils.c var_utils_2.c quotes.c exp_exit.c ft_unset.c \
  	ft_env.c ft_pwd.c init.c ft_export.c export_utils.c \
	ft_exit.c ft_echo.c ft_cd.c exec.c check_files.c exec_builtin.c \
	ft_utils.c handlers_flags.c error_handler.c exec_child.c \
	space_split.c exp_token.c heredoc_create.c redirs_handler.c \
	env_init.c ft_more_utils.c

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
