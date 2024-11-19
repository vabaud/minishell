/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:13:26 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/19 20:10:56 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	tokenize_input(char *s)
{
	int		i;
	t_token	*token;

	i = 0;
	token = NULL;
	while (s[i])
	{
		while (ft_strchr(" \t\n", s[i]))
			i++;
		if (ft_strchr("><|", s[i]))
			i = handle_special_chars(s, i, &token);
		else
			i = handle_word(s, i, &token);
	}
	display_tokens(token);
	return (0);
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
		if (s[start] == '\'' || s[start] == '\"')
		{
			while (s[++i] != s[start] && s[i])
				;
			i++;
			break ;
		}
		else if (s[i] == '\'' || s[i] == '\"')
			break ;
		if (!in_quotes(s[i]) && ft_strchr(" \t\n><|", s[i]))
			break ;
		i++;
	}
	if ((s[start] == '\'' || s[start] == '\"') && (s[i - 1] == '\'' || s[i
			- 1] == '\"'))
		add_token(token, new_token(TOKEN_WORD, ft_substr(s, start + 1, i - start
					- 2)));
	else
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
		printf("Token: \033[0;36m %-20s \033[0m |\t \
			Type: \033[0;35m %-18s \033[0m \n",
				token->value,
				get_token_type_name(token->type));
		printf("--------------------------------------------------\n");
		token = token->next;
	}
}
