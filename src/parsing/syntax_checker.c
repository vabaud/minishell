/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:25:48 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/18 17:30:23 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_syntax_error(char *msg)
{
    ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
    ft_putstr_fd(msg, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
    g_exit_code = 2;
}

int	syntax_error_checker(char *s)
{
	if (has_unclosed_quotes(s))
    {
        g_exit_code = 2;
		return (ft_putstr_fd("Syntax error: unclosed quote\n", STDERR_FILENO), 0);
    }
	else if (has_logical_operators(s))
    {
        g_exit_code = 2;
		return (ft_putstr_fd("Error: Logical operators '&&' and '||' \
are not supported.\n", STDERR_FILENO), 0);
    }
	else if (has_misplaced_operators(s))
    {
        g_exit_code = 2;
		return (ft_putstr_fd("Syntax error: misplaced operator\n", STDERR_FILENO), 0);
    }
	else if (has_invalid_redirections(s))
    {
        g_exit_code = 2;
		return (ft_putstr_fd("Syntax error: invalid redirection\n", STDERR_FILENO), 0);
    }
	return (1);
}

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
		if ((s[i] == '&' && s[i + 1] == '&') || (s[i] == '|' && s[i
				+ 1] == '|'))
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
	// if (s[start] == '>' || s[start] == '<' || s[end] == '>' || s[end] == '<')
	// 	return (1);
	while (s[start])
	{
		if ((s[start] == '>' || s[start] == '<') && (s[start + 1] == '>'
				|| s[start + 1] == '<') && (s[start + 2] == '>' || s[start
				+ 2] == '<'))
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

int	syntax_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type >= 2 && tmp->type <= 5 && !tmp->next)
			return (print_syntax_error("newline"), 0);
		else if (tmp->type == TOKEN_PIPE && tmp->next
			&& tmp->next->type == TOKEN_PIPE)
			return (print_syntax_error("|"), 0);
		else if (tmp->type >= 2 && tmp->type <= 5 && tmp->next
			&& tmp->next->type != TOKEN_WORD)
			return (print_syntax_error(token->next->value), 0);
		tmp = tmp->next;
	}
	return (1);
}
