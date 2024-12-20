/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:25:48 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 11:12:48 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_syntax_error(char *msg)
{
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	g_exit_code = 2;
}

int	syntax_error_checker(char *s)
{
	if (has_unclosed_quotes(s))
		ft_putstr_fd("Syntax error: unclosed quote\n", STDERR_FILENO);
	else if (has_logical_operators(s))
		ft_putstr_fd("Error: Logical operators '&&' and '||' \
are not supported.\n", STDERR_FILENO);
	else if (has_misplaced_operators(s))
		ft_putstr_fd("Syntax error: misplaced operator\n", STDERR_FILENO);
	else if (has_invalid_redirections(s))
		ft_putstr_fd("Syntax error: invalid redirection\n", STDERR_FILENO);
	if (has_unclosed_quotes(s) || has_logical_operators(s)
		|| has_misplaced_operators(s) || has_invalid_redirections(s))
	{
		g_exit_code = 2;
		return (0);
	}
	return (1);
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
