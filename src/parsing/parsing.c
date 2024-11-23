/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:00:58 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/23 18:30:33 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_token(t_token *token)
{
	t_command	*cmd;
	t_command	*current;

	cmd = NULL;
	current = new_command();
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			add_command(&cmd, current);
			current = new_command();
		}
		else if (token->type == TOKEN_WORD)
			add_arg(current, token->value);
		else if (token->type >= 2 && token->type <= 4)
		{
			if (!set_redirection(current, token))
				return ;
			token = token->next;
		}
		token = token->next;
	}
	add_command(&cmd, current);
	print_cmd(cmd);
}

void	add_command(t_command **cmd, t_command *new_cmd)
{
	t_command	*last;

	last = NULL;
	if ((*cmd) == NULL)
		(*cmd) = new_cmd;
	else
	{
		last = (*cmd);
		while (last->next != NULL)
			last = last->next;
		last->next = new_cmd;
	}
}

void	add_arg(t_command *cmd, char *new_str)
{
	int		i;
	char	**new_arg;

	i = 0;
	if (!cmd || !new_str)
		return ;
	while (cmd->args && cmd->args[i])
		i++;
	new_arg = malloc(sizeof(char *) * (i + 2));
	if (!new_arg)
		return ;
	i += 1;
	new_arg[i--] = NULL;
	new_arg[i--] = ft_strdup(new_str);
	while (i >= 0)
	{
		new_arg[i] = ft_strdup(cmd->args[i]);
		i--;
	}
	if (cmd->args)
	{
		free(cmd->args);
	}
	cmd->args = new_arg;
}

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
	if (!open(file, O_RDONLY))
	{
		return (0);
	}
	return (1);
}

// void handle_heredoc(t_command *cmd, t_token *token)
// {
//     t_token *new_token;

//     new_token = token;
// }