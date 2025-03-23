#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_type
{
	CMD,         // Command (e.g., "ls", "cat")
	ARG,         // Argument (e.g., "-a", "file.txt")
	PIPE,        // Pipe ("|")
	REDIR_IN,    // Input redirection ("<")
	REDIR_OUT,   // Output redirection (">")
	REDIR_APPEND,// Append redirection (">>")
	HERE_DOC,    // Here document ("<<")
	ENV_VAR,     // Environment variable ("$HOME")
	//S_QUOTE,     // Quoted string ('...')
	//D_QUOTE,	 // Quoted string ("...")
	//SEP,         // Separator (e.g., ";")
	//OPERATOR,    // Logical operators ("&&", "||")
	//SUBSHELL,     // Subshell ("(cmd)")
	UNKNOWN
}	t_type;

typedef struct	s_input
{
	char 			*content;
	enum e_type		type;
	int				position;
	struct s_input		*next;
	struct s_input		*prev;
}				t_input;

//main
void init_input(t_input *first);
int  save_input(char *line, t_input **first);

//free
void free_split(char **split);
void	free_list(t_input *first);

//list utils
t_input	*add_new(char *content, int pos, t_input *prev);
t_input	*make_new_node(char *content, int pos);
int	list_size(t_input *lst);

//check input
int	pipe_syntax(t_input *cur, t_input *first);
int redir_syntax(t_input *cur, t_input *first);
int quotes_syntax(t_input *cur);
int is_red_or_pipe(t_input *first);
int	syntax_check(t_input *first);
int	assign_type(t_input **first);

//tests
const char *get_type_str(enum e_type type);
void	test_print(t_input *first);

//Split test
char	**mini_split(char const *s);

# endif
