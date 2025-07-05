#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

typedef enum e_type
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,
	UNKNOWN
}					t_type;

typedef struct s_input
{
	char			*content;
	enum e_type		type;
	int				is_builtin;
	int				exp;
	int position; // do we need it? NOPE
	struct s_input	*next;
	struct s_input	*prev;
}					t_input;

typedef struct s_cmd
{
	char			**args;
	char			**in;
	char			**out;
	int				in_redirs;
	int				out_redirs;
	int				*redir_order;
	int				in_index;
	int				out_index;
	int				is_builtin;
	int				append;
	int				is_hd;
	char			*hd_in;
	char			**hd_content;
	char			*limiter;
	int				error_skip;
}					t_cmd;

typedef struct s_data
{
	char			**env_path;
	char			**envp;
	pid_t			*pid;
	int				**pipes;
	int				fd1;
	int				fd2;
	t_cmd			*cmds;
	int				cmd_count;
	int				ec_update_flag;
}					t_data;

void				fail_mall(void);

// main
int					return_exit_code(int exit);
int					return_sig_flag(int sig);

// syntax
int					syntax_check(t_input *first);
int					assign_type(t_input **first);

// syntax utils
int					is_red_or_pipe(t_input *first);
int					is_red(t_input *cur);
void				syntax_err(void);

// env_var
int					find_ev(t_input *first, t_data *data);
int					expand_var(char **content, char **envp);
int					join_all(char **content, char *start, char *end, char *var);
char				*save_rest(char *content, char *var);
char				*save_start(char *content);

// var utils
char				*search_var(char *content, char *var);
int					stop(char *content);
char				*extract_var(char **envp, char *var);
char				*save_var(char *content);
int					start_len(char *content);

// exp token
int					exp_tokenise(t_input *cur, char **envp);
char				*save_unquoted_start(char *content, int i, char **env);
int					unquoted_var(char *content);
t_input				*new_token(t_input *cur, char *start, char *exp,
						char *next);

// var utils 2
t_input				*add_node(t_input *cur, char *content);
t_input				*empty(t_input *cur, char *start, char *next, char *exp);
t_input				*middle(t_input *cur, char **split);
t_input				*end(t_input *cur, char *next, int f_e);
t_input				*beginning(t_input *cur, char *start, char *exp, int f_b);



int					check_quotes(char *content, int len);
int					expand_exit(t_input **cur, t_data *data);

int					start_len(char *content);
int					even_odd(char *content, int i);
int					find_index(int i /*  int j, */);
int					exp_helper(char *content);

int					exp_split(t_input *first);
int					count_word(char *content);
int					ft(t_input *cur, char *exp, char *next, char *start);
char				*save_unquoted_start(char *content, int i, char **env);
int					unquoted_var(char *content);
t_input				*add_node(t_input *cur, char *content);
// init
void				init_input(t_input *first);
int					save_input(char *line, t_input **first);
int					copy_envp(t_data *data, char **envp);
// space split
char				**space_split(char const *s);

// free
void				free_split(char **split);
void				free_list(t_input *first);

// list utils
t_input				*add_new(char *content, int pos, t_input *prev);
t_input				*make_new_node(char *content, int pos);
int					list_size(t_input *lst);

// quotes
int					check_quotes(char *content, int len);
int					remove_useless_quotes(char **content, int len);
int					remove_quotes(t_input *input/* , t_data *data */);
int					return_final_len(char *str);
// commands

int					compare_cmd(t_input *cur, char **commands);
int					find_cmd(t_input *first /* , t_data *data */);

// exit exp
int					find_exit(t_input *first, t_data *data);

// tests
const char			*get_type_str(enum e_type type);
void				test_print(t_input *first);

// Split test
char				**mini_split(char const *s);

// builtinss
void				ft_echo(t_cmd *cmd);
void				ft_exit(t_data *data, t_cmd *cmd);
void				ft_cd(t_data *data, t_cmd *cmd);

int					ft_unset(t_data *data, t_cmd *cmd);

int					arr_len(char **arr);

// export
int					add_env(t_data *data, char *var, char *content);
char				*double_join(char *s1, char *s2, char *s3);
void				ft_export(t_data *data, t_cmd *cmd);
int					return_exit_code(int exit);
char				*get_var(char *str);
char				*get_content(char *str);
int					print_export(char **envp);

// check_files
void				add_skip_flag(t_cmd *cmd, int i, int cmd_count, int mode);
int					check_out(t_data *data, int i);
int					check_in(t_data *data, int i);

// ft_utils
int					ft_strcmp(const char *s1, const char *s2);
int					is_space(char c);
int					count_word(char *content);
int					get_env_path(t_data *data, char **envp);
void				count_cmds(t_input *tokens, t_data *data);


// signal_handlers
void				child_handler(int sig);
void				hd_handler(int sig);

// exec builtin
void				exec_builtin_child(t_cmd *cmd, t_data *data);
int					exec_builtin_parent(t_cmd *cmd, t_data *data);

// exec child
int					exec_child(t_data *data, int index, char **envp);

// heredoc
int					set_heredoc_fds(t_cmd *cmd, int index);
int					handle_heredoc(t_cmd *cmd, t_input **cur, char **envp);
void				exec_hd(t_data *data, t_cmd *cmd, int index);

// error_handler
void				handle_error(char *str, int error_code);

// free_all
void				free_cmd(t_cmd *cmd);
void				free_str_arr(char **str);
void				free_pipes(int ***pipes, int count);
void				close_fd(int *fd);
void				free_all(t_data *data);

// heredoc_create
int	create_heredoc(t_cmd *cmd, char **envp);

// redirs handler 
int					count_redirs(t_cmd *cmd, t_input *input, t_input *start);
void				handle_redirs(t_cmd *cmd, t_input **cur);
int					open_files(t_data *data);




int					parse_tokens(t_input *tokens, t_data *data);

int					exec_proc(t_data *data, char **envp);
int					create_pipes(t_data *data);

void				print_cmd_list(t_cmd *cmds);
void				print_cmds(t_data *data);

// Builtins
void				ft_pwd(void);
void				ft_env(char **env);

#endif
