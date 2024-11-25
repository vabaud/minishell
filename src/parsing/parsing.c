/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:00:58 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/25 14:57:50 by vabaud           ###   ########.fr       */
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

// void handle_heredoc(t_command *cmd, t_token *token)
// {
//     t_token *new_token;

//     new_token = token;
// }