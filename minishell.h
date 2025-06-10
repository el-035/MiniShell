#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
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
	UNKNOWN
}	t_type;

typedef struct	s_input
{
	char 			*content;
	enum e_type		type;
	int				is_builtin;
	char			*cmd_path;		//needs to be added to free ft
	int				position;
	struct s_input		*next;
	struct s_input		*prev;
}				t_input;

typedef struct s_cmd
{
   // struct s_cmd    *next;
    char 			**args;        // [ls, -l, NULL]
    char *in;
    char *out;
	int	is_builtin;
    int append;
	int	is_hd;
	char **hd_content;
	char *limiter;
}               t_cmd;

typedef struct s_data
{
    char		**env_path;
	char		**envp;
    pid_t 		*pid;
    int           **pipes;
    int           fd1;
    int           fd2;
    t_cmd 			*cmds;
    int           cmd_count;
    //int           mod;
}                 t_data;

//main

int	return_exit_code(int exit);
int	return_sig_flag(int sig);

//init
void init_input(t_input *first);
int  save_input(char *line, t_input **first);
int	copy_envp(t_data *data, char **envp);

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

//env_var
int	find_ev(t_input *first, t_data *data);
int	expand_var(t_input **cur, t_data *data);
//char	*extract_var(t_data *data, char *var);
int	check_quotes(char *content, int len);
int	join_all(t_input **cur, char *start, char *end, char *var);
int	expand_exit(t_input **cur, t_data *data);

//var utils
int	start_len(char *content);
char	*search_var(char *content, char *var);
int	stop(char *content);
char *extract_var(char **envp, char *var);
char	*save_var(char *content);
int even_odd(char *content, int i);

//quotes
int	check_quotes(char *content, int len);
int	remove_useless_quotes(t_input *cur);

//commands

int compare_cmd(t_input *cur, char **commands);
int	find_cmd(t_input *first/* , t_data *data */);

//exit exp
int	find_exit(t_input *first, t_data *data);

//tests
const char *get_type_str(enum e_type type);
void	test_print(t_input *first);

//Split test
char	**mini_split(char const *s);

//builtinss
void	ft_echo(t_cmd *cmd);
void	ft_exit(t_data *data, t_cmd *cmd);
void	ft_cd(t_data *data, t_cmd *cmd);
void	ft_unset(t_data *data, t_cmd *cmd);
int arr_len(char **arr);

int	return_exit_code(int exit);

//Exec
int	check_permission(t_data *data, char *fd_name, int file_order);
int	get_env_path(t_data *data, char **envp);
int open_files(t_data *data);

void	free_cmds(t_cmd *cmd);
void	free_cmd(t_cmd *cmd);
void	free_str_arr(char **str);
void	free_pipes(int ***pipes, int count);
void	close_fd(int *fd);
void	free_all(t_data *data);
void	handle_error(char *str, int error_code);

int	parse_tokens(t_input *tokens, t_data *data);

int ft_strcmp(const char *s1, const char *s2);
char	*check_path(t_data *data, char *cmd);
int execute_cmd(t_data *data, char **args, char **envp);
int	exec_child(t_data *data, int index, char **envp);
int exec_proc(t_data *data, char **envp);
int	create_pipes(t_data *data);

void print_cmd_list(t_cmd *cmds);
void print_cmds(t_data *data);

int	handle_heredoc(t_cmd *cmd, t_input **cur);

//Builtins
void ft_pwd();
void ft_env(char **env);

# endif
