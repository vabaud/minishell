/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:54:25 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/17 19:23:34 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_redirection(t_command *cmd, t_token *token, t_all *all)
{
	if (token->type == TOKEN_REDIR_IN)
	{
		if (!set_input(cmd, token->next->value, all))
			return (0);
	}
	else if (token->type == TOKEN_REDIR_HEREDOC)
	{
		handle_heredoc(cmd, token, all);
	}
	else if (token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_APPEND)
	{
		if (!set_out_or_append(cmd, token->next->value, token->type, all))
			return (0);
	}
	return (1);
}

int	set_input(t_command *cmd, char *file, t_all *all)
{
	if (cmd->input_file)
	{
		free(cmd->input_file);
	}
	cmd->input_file = replace_env(remove_quotes(file), all);
	return (1);
}

int	set_out_or_append(t_command *cmd, char *file, t_token_type type, t_all *all)
{
    int fd;
    fd = open(file, O_CREAT | O_RDONLY, 0644);
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->append_mode == 1 && type == TOKEN_REDIR_OUT)
		cmd->append_mode = 0;
	else if (type == TOKEN_REDIR_APPEND)
		cmd->append_mode = 1;
	cmd->output_file = replace_env(remove_quotes(file), all);
    close(fd);
	if (!cmd->output_file)
		return (0);
	return (1);
}
