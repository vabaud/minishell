/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:54:25 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/25 16:11:24 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_redirection(t_command *cmd, t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
	{
		if (!set_input(cmd, token->next->value))
			return (0);
	}
	else if (token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND)
	{
		if (!set_out_or_append(cmd, token->next->value, token->type))
			return (0);
	}
	return (1);
}

int	set_input(t_command *cmd, char *file)
{
	if (cmd->input_file)
	{
		free(cmd->input_file);
	}
	cmd->input_file = remove_quotes(file);
	if (!open(file, O_RDONLY))
		return (0);
	return (1);
}

int	set_out_or_append(t_command *cmd, char *file, t_token_type type)
{
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->append_mode == 1 && type == TOKEN_REDIR_OUT)
		cmd->append_mode = 0;
	else if (type == TOKEN_REDIR_APPEND)
		cmd->append_mode = 1;
	cmd->output_file = remove_quotes(file);
	if (cmd->append_mode)
	{
		if (!open(file, O_CREAT | O_APPEND | O_RDWR))
			return (0);
	}
	else if (!open(file, O_CREAT | O_RDWR | O_TRUNC))
		return (0);
	return (1);
}
