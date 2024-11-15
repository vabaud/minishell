/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:37:24 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/13 20:12:44 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"

// Token type enumeration
typedef enum e_token_type
{
    TOKEN_WORD,      // For commands and arguments
    TOKEN_PIPE,      // For '|'
    TOKEN_REDIR_IN,  // For '<'
    TOKEN_REDIR_OUT, // For '>'
    TOKEN_REDIR_APPEND, // For '>>'
    TOKEN_REDIR_HEREDOC, // For '<<'
    TOKEN_ENV_VAR, // For environment variables
}   t_token_type;

// Token structure
typedef struct s_token
{
    t_token_type type;
    char        *value;
    struct s_token *next;
}   t_token;

int	main(void);
int	pwd(void);
int	has_unclosed_quotes(char *s);
int has_logical_operators(char *s);
int has_invalid_redirections(char *s);
int syntax_error_checker(char *s);
int has_misplaced_operators(char *s);

#endif