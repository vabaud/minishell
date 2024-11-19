/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:37:24 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/19 19:19:18 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>

// Token type enumeration
typedef enum e_token_type
{
	TOKEN_WORD,          // For commands and arguments
	TOKEN_PIPE,          // For '|'
	TOKEN_REDIR_IN,      // For '<'
	TOKEN_REDIR_OUT,     // For '>'
	TOKEN_REDIR_APPEND,  // For '>>'
	TOKEN_REDIR_HEREDOC, // For '<<'
	TOKEN_ENV_VAR,       // For environment variables
}					t_token_type;

// Token structure
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

int					main(void);
int					pwd(void);
int					has_unclosed_quotes(char *s);
int					has_logical_operators(char *s);
int					has_invalid_redirections(char *s);
int					syntax_error_checker(char *s);
int					has_misplaced_operators(char *s);
t_token				*new_token(t_token_type type, char *value);
void				add_token(t_token **token, t_token *new_token);
void				display_tokens(t_token *tokens);
const char			*get_token_type_name(t_token_type type);
int					handle_word(char *s, int i, t_token **token);
int					handle_special_chars(char *s, int i, t_token **token);
int					tokenize_input(char *s);
int					in_quotes(char c);
int close_quotes(char c);

#endif