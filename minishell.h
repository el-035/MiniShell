#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	S_QUOTE,     // Quoted string ('...' or "...")
	D_QUOTE,	 // Quoted string ('...' or "...")
	SEP,         // Separator (e.g., ";")
	OPERATOR,    // Logical operators ("&&", "||")
	SUBSHELL     // Subshell ("(cmd)")
}	t_type;

typedef struct	s_input
{
	char 		*content;
	t_type		*type;
	int			position;
	t_input		*next;
	t_input		*prev;
}				t_input

# endif