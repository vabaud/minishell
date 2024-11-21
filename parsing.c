/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:00:58 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/21 15:14:11 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	add_command(t_command **cmd, t_command *new_cmd)
{
	t_command	*last;

	if (cmd == NULL)
		cmd = new_cmd;
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
	int	i;
    char **new_arg;

	i = 0;
    while (cmd->args && cmd->args[i])
        i++;
    new_arg = malloc(sizeof(char *) * (i + 2));
    if (!new_arg)
        return NULL;
    i += 2;
    new_arg[i--] = NULL;
    new_arg[i--] = ft_strdup(new_str);
    while (i > 0)
    {
        new_arg[i] = ft_strdup(cmd->args[i]);
        i--;
    }
}

int set_redirection(t_command *cmd, char *file, t_token *token)
{
    if (token->type == TOKEN_REDIR_IN)
        cmd->input_file = ft_strdup(file);
    else if (token->type == TOKEN_REDIR_OUT)
    {
        cmd->output_file = ft_strdup(file);
        if (cmd->append_mode == 1)
            cmd->append_mode = 0;
    }
    else if (token->type == TOKEN_REDIR_APPEND)
    {
        cmd->output_file = ft_strdup(file);
        cmd->append_mode = 1;
    }
    return 1;
}   

int set_input(t_command *cmd, char *file)
{
    if (cmd->input_file)
    {
        free(cmd->input_file);
        cmd->input_file = ft_strdup(file);
    }
    if (!open(file, O_RDONLY))
        return 0;
    return 1;
}

int set_out_or_append(t_command *cmd, char *file, t_token_type type)
{
    if (cmd->output_file)
    {
        free(cmd->output_file);
        cmd->output_file = ft_strdup(file);
        if (cmd->append_mode == 1 && type == TOKEN_REDIR_OUT)
            cmd->append_mode = 0;
        else if (type == TOKEN_REDIR_APPEND)
            cmd->append_mode = 1;
        if (!open(file, O_RDONLY))
            return 0;
    }
    return 1;
}

void handle_heredoc(t_command *cmd, char);
