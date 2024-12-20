/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:00:58 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/21 12:56:35 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*browse_token(t_token *token, t_all *all, t_command *cmd)
{
	t_command	*current;

	current = new_command();
	while (token)
	{
		token->value = remove_quotes(replace_env(token->value, all));
		if (token->type == TOKEN_PIPE)
		{
			add_command(&cmd, current);
			current = new_command();
		}
		else if (token->type == TOKEN_WORD)
			add_arg(current, token->value);
		else if (token->type >= 2 && token->type <= 5)
		{
			if (!set_redirection(current, token, all))
				return (NULL);
			token = token->next;
		}
		token = token->next;
	}
	add_command(&cmd, current);
	return (cmd);
}

t_command	*parse_token(t_token *token, t_all *all)
{
	t_command	*cmd;
	t_token		*tmp;

	cmd = NULL;
	tmp = token;
	cmd = browse_token(token, all, cmd);
	free_token(tmp);
	g_exit_code = 0;
	return (cmd);
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
		last->next->prev = last;
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
		free_env(cmd->args);
	}
	cmd->args = new_arg;
}
