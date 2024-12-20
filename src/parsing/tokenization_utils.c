/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:52:56 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 10:53:52 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(value);
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **token, t_token *new_token)
{
	t_token	*last;

	if (!(*token))
		(*token) = new_token;
	else
	{
		last = (*token);
		while (last->next != NULL)
			last = last->next;
		last->next = new_token;
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

int	in_quotes(char c)
{
	static char	q_char = '\0';
	static int	q_count = 0;

	if (c == '\'' || c == '\"')
	{
		if (q_count == 1 && c == q_char)
		{
			q_count = 0;
		}
		else if (q_count == 0)
		{
			q_char = c;
			q_count = 1;
			return (0);
		}
	}
	return (q_count);
}
