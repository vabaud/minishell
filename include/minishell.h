/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:37:24 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 17:48:20 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_command
{
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_mode;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_all
{
	t_command			*cmd;
	char				**env;
}						t_all;

typedef struct s_pipe_info
{
	int					prev_pipe_fd;
	int					pipe_fd[2];
	int					i;
	pid_t				*pid;
}						t_pipe_info;

extern int				g_exit_code;

// MAIN
int						main(int ac, char **av, char **envp);
void					shell_loop(t_all *all, t_token *token);
void					print_env(char **env);

// BUILTINS
void					ft_cd(t_all *all, t_command *cmd);
int						val_numb(const char *str);
void					ft_exit(char **args, t_all *all, pid_t *pid);
int						ft_echo(t_command *cmd);
int						ft_unset(t_all *all, char **args);
void					remove_env(t_all *all, char *s);
int						valid_indentifier(const char *str);
int						add_n_up_env(t_all *all, const char *var);
int						browse_env(char **env, const char *var, char *name,
							int name_len);
void					ft_export(t_all *all, char **args);
int						ft_pwd(void);
int						execute_builtins(t_all *all, t_command *cmd,
							t_pipe_info *pipe_info);
int						ft_env(char **env, t_command *cmd);
int						is_builtin(t_command *cmd);
void					sort_tab(char **env);
void					print_var(char *env, char **env_tab);
int						count_arg(char **params);

// TOKENIZATION
t_token					*new_token(t_token_type type, char *value);
void					add_token(t_token **token, t_token *new_token);
int						handle_word(char *s, int i, t_token **token);
int						handle_special_chars(char *s, int i, t_token **token);
t_token					*tokenize_input(char *s);
int						in_quotes(char c);
void					free_token(t_token *token);
void					display_tokens(t_token *tokens);
const char				*get_token_type_name(t_token_type type);

// SYNTAX_CHECKER
int						has_unclosed_quotes(char *s);
int						has_logical_operators(char *s);
int						has_invalid_redirections(char *s);
int						syntax_error_checker(char *s);
int						has_misplaced_operators(char *s);
int						syntax_token(t_token *token);

// PARSING
void					heredoc_handler(int signal);
void					handle_heredoc(t_command *cmd, t_token *token,
							t_all *all);
t_command				*parse_token(t_token *tokens, t_all *all);
void					add_command(t_command **cmd, t_command *new_cmd);
void					add_arg(t_command *cmd, char *new_str);
t_command				*new_command(void);
int						set_redirection(t_command *cmd, t_token *token,
							t_all *all);
int						set_input(t_command *cmd, char *file, t_all *all);
int						set_out_or_append(t_command *cmd, char *file,
							t_token_type type, t_all *all);
void					print_cmd(t_command *commands);
void					free_cmd(t_command *cmd);

// UTILS
int						ft_cmdsize(t_command *lst);
char					*remove_quotes(char *str);
int						in_s_quote(char *s, int i);

// ENV
char					*replace_env(char *s, t_all *all);
char					*env_value(char *s, char **env_tab);
void					free_env(char **env);
char					**change_env_value(char *env, char **env_tab,
							char *value);
char					**env_cpy(char **env);

// EXEC
void					execute_pipeline(t_all *all);
// void					exec_cmd(t_command *cmd, t_all *all, pid_t *pid);
void					exec_cmd(t_command *cmd, t_all *all,
							t_pipe_info *pipe_info);
char					*get_path(char *cmd, char **env);
void					free_all_exec(t_all *all, t_pipe_info *pipe_info);
void					pipe_loop(t_command *cmd, t_all *all,
							t_pipe_info *pipe_info);
void					parent_process(t_pipe_info *pipe_info, t_command *cmd);
// void					redirect_output(const char *file, int append);
void					redirect_output(t_command *cmd, t_pipe_info *pipe_info);
// void					redirect_input(const char *);
void					redirect_input(t_command *cmd, t_pipe_info *pipe_info, t_all *all);
void					wait_children(t_pipe_info *pipe_info);

// SIGNAL
void					sigaction_handle(void);
void					init_signals(void);
void					handle_sigquit(int signal);
void					handle_sigint(int signal);
void					handle_sigint_cmd(int signal);

#endif