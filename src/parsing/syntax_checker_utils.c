/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:12:06 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 11:14:24 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_unclosed_quotes(char *s)
{
	int		i;
	char	t_quote;

	i = 0;
	t_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"'))
		{
			if (s[i] == t_quote)
				t_quote = 0;
			else if (t_quote == 0)
				t_quote = s[i];
		}
		i++;
	}
	if (t_quote != 0)
		return (1);
	return (0);
}

int	has_logical_operators(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '&' && s[i + 1] == '&')
			|| (s[i] == '|' && s[i + 1] == '|'))
			return (1);
		i++;
	}
	return (0);
}

int	has_invalid_redirections(char *s)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s) - 1;
	while ((s[start] == ' ' || s[start] == '\t') && s[start] != '\0')
		start++;
	while ((s[end] == ' ' || s[end] == '\t') && end > 0)
		end--;
	while (s[start])
	{
		if ((s[start] == '>' || s[start] == '<') && (s[start + 1] == '>'
				|| s[start + 1] == '<') && (s[start + 2] == '>'
				|| s[start + 2] == '<'))
			return (1);
		start++;
	}
	return (0);
}

int	has_misplaced_operators(char *s)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s) - 1;
	while ((s[start] == ' ' || s[start] == '\t') && s[start] != '\0')
		start++;
	while ((s[end] == ' ' || s[end] == '\t') && end > 0)
		end--;
	if (s[start] == '|' || s[end] == '|')
		return (1);
	return (0);
}
