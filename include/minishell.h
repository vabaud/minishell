/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:37:24 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/25 14:58:14 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
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
}						t_command;

int						main(void);
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
int						in_quotes(char c);
int						close_quotes(char c);
char					*remove_quotes(char *str);
void					parse_token(t_token *tokens);
void					add_command(t_command **cmd, t_command *new_cmd);
void					add_arg(t_command *cmd, char *new_str);
int						set_redirection(t_command *cmd, t_token *token);
int						set_input(t_command *cmd, char *file);
int						set_out_or_append(t_command *cmd, char *file,
							t_token_type type);
t_command				*new_command(void);
void					print_cmd(t_command *commands);
void					free_cmd(t_command *cmd);

#endif