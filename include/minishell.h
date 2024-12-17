/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:37:24 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/17 18:33:12 by vabaud           ###   ########.fr       */
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
	TOKEN_WORD,          // For commands and arguments
	TOKEN_PIPE,          // For '|'
	TOKEN_REDIR_IN,      // For '<'
	TOKEN_REDIR_OUT,     // For '>'
	TOKEN_REDIR_APPEND,  // For '>>'
	TOKEN_REDIR_HEREDOC, // For '<<'
	TOKEN_ENV_VAR,       // For environment variables
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
	int					exit_code;
}						t_all;

extern int				g_received_signal;

int						main(int ac, char **av, char **envp);
int						pwd(void);
int						has_unclosed_quotes(char *s);
int						has_logical_operators(char *s);
int						has_invalid_redirections(char *s);
int						syntax_error_checker(char *s);
int						has_misplaced_operators(char *s);
t_token					*new_token(t_token_type type, char *value);
void					add_token(t_token **token, t_token *new_token);
void					display_tokens(t_token *tokens);
const char				*get_token_type_name(t_token_type type);
int						handle_word(char *s, int i, t_token **token);
int						handle_special_chars(char *s, int i, t_token **token);
t_token					*tokenize_input(char *s);
void					free_token(t_token *token);
int						in_quotes(char c);
int						close_quotes(char c);
char					*remove_quotes(char *str);
t_command				*parse_token(t_token *tokens, t_all *all);
void					add_command(t_command **cmd, t_command *new_cmd);
void					add_arg(t_command *cmd, char *new_str);
int						set_redirection(t_command *cmd, t_token *token,
							t_all *all);
int						set_input(t_command *cmd, char *file, t_all *all);
int						set_out_or_append(t_command *cmd, char *file,
							t_token_type type, t_all *all);
t_command				*new_command(void);
void					print_cmd(t_command *commands);
void					free_cmd(t_command *cmd);
char					**env_cpy(char **env);
char					*replace_env(char *s, t_all *all);
char					*env_value(char *s, char **env_tab);
void					handle_heredoc(t_command *cmd, t_token *token,
							t_all *all);
void					restore_sigint(void);
void					sigaction_handle(void);
void					init_signals(void);
void					handle_sigquit(int signal);
void					handle_sigint(int signal);
char					**change_env_value(char *env, char **env_tab,
							char *value);
void					ft_cd(t_all *all, t_command *cmd);
int						val_numb(const char *str);
void					ft_exit(char **args);
int						count_arg(char **params);
void					ft_echo(t_command *cmd);
void					free_env(char **env);
void					remove_env(t_all *all, char *s);
void					execute_pipeline(t_all *all);
void					exec_cmd(t_command *cmd, t_all *all);
char					*get_path(char *cmd, char **env);
void					ft_unset(t_all *all, char **args);
int						valid_indentifier(const char *str);
void					add_n_up_env(t_all *all, const char *var);
int						browse_env(char **env, const char *var, char *name,
							int name_len);
void					ft_export(t_all *all, char **args);
int						ft_pwd(void);
void					print_env(char **env);
int						ft_cmdsize(t_command *lst);
void					handle_sigquit(int signal);
void					heredoc_handler(int signum);
int						execute_builtins(t_all *all, t_command *cmd);
int						ft_env(char **env, t_command *cmd);
void					setup_interactive_signals(void);
void					setup_child_process_signals(void);
int						is_builtin(t_command *cmd);

#endif