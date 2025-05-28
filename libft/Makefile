NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror 

SRC = ft_split.c ft_strncmp.c ft_strtrim.c ft_strlen.c ft_strdup.c ft_calloc.c ft_strjoin.c ft_strchr.c ft_isalpha.c ft_memset.c ft_itoa.c ft_strnstr.c get_next_line.c get_next_line_utils.c ft_strlcpy.c ft_strlcat.c


SRCB = #ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c

OBJ = $(SRC:.c=.o)

OBJB = $(SRCB:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

BONUSFLAG = .bonus

$(BONUSFLAG): $(OBJB)
	ar rcs $(NAME) $?
	@touch $(BONUSFLAG)

bonus: $(NAME) $(BONUSFLAG) 

clean:
	rm -f $(OBJ) $(OBJB)

fclean:
	rm -f $(NAME) $(OBJ) $(OBJB)

re: fclean all

.PHONY: all clean fclean re bonus
