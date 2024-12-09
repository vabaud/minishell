/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:13:26 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/12 17:02:00 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tokenize_input(char *s)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (s[i])
	{
		while (s[i] && ft_strchr(" \t\n", s[i]))
			i++;
		if (s[i] && ft_strchr("><|", s[i]))
			i = handle_special_chars(s, i, &token);
		else if (s[i])
			i = handle_word(s, i, &token);
	}
	// display_tokens(token);
	return (token);
}

int	handle_special_chars(char *s, int i, t_token **token)
{
	if (s[i] == '>')
	{
		if (s[++i] == '>')
		{
			add_token(token, new_token(TOKEN_REDIR_APPEND, ">>"));
			i++;
		}
		else
			add_token(token, new_token(TOKEN_REDIR_OUT, ">"));
	}
	else if (s[i] == '<')
	{
		if (s[++i] == '<')
		{
			add_token(token, new_token(TOKEN_REDIR_HEREDOC, "<<"));
			i++;
		}
		else
			add_token(token, new_token(TOKEN_REDIR_IN, "<"));
	}
	else if (s[i++] == '|')
		add_token(token, new_token(TOKEN_PIPE, "|"));
	return (i);
}

int	handle_word(char *s, int i, t_token **token)
{
	int	start;

	start = i;
	while (s[i])
	{
		if (!in_quotes(s[i]) && ft_strchr(" \t\n><|", s[i]))
			break ;
		i++;
	}
	add_token(token, new_token(TOKEN_WORD, ft_substr(s, start, i - start)));
	return (i);
}

const char	*get_token_type_name(t_token_type type)
{
	const char	*token_type_names[7];

	token_type_names[0] = "WORD";
	token_type_names[1] = "PIPE";
	token_type_names[2] = "REDIRECT_IN";
	token_type_names[3] = "REDIRECT_OUT";
	token_type_names[4] = "REDIRECT_APPEND";
	token_type_names[5] = "REDIRECT_HEREDOC";
	token_type_names[6] = "TOKEN_ENV_VAR";
	if (type >= 0 && type < 7)
		return (token_type_names[type]);
	return ("UNKNOWN");
}

void	display_tokens(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		ft_printf("Token: \033[0;36m %s \033[0m |\t \
			Type: \033[0;35m %s \033[0m \n", token->value,
			get_token_type_name(token->type));
		ft_printf("--------------------------------------------------\n");
		token = token->next;
	}
}
