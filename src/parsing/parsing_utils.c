/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:02:04 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/23 18:30:29 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_mode = 0;
	cmd->next = NULL;
	return (cmd);
}

void	print_cmd(t_command *commands)
{
	t_command	*cmd;
	int			i;

	cmd = commands;
	i = -1;
	while (cmd)
	{
		ft_printf("-----------------------------\n");
		while (cmd->args && cmd->args[++i])
			ft_printf("Args[%d] = %s\n", i, cmd->args[i]);
		ft_printf("Input File = %s\n", cmd->input_file);
		ft_printf("Output File = %s\n", cmd->output_file);
		ft_printf("Append Mode = %d\n", cmd->append_mode);
		ft_printf("-----------------------------\n");
		cmd = cmd->next;
        i = -1;
	}
}

void free_cmd(t_command *cmd)
{
    t_command *tmp;
    int i;

    i = 0;
    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        while (tmp->args && tmp->args[i])
            free(tmp->args[i++]);
        if (tmp->args)
            free(tmp->args);
        free(tmp->input_file);
        free(tmp->output_file);
        free(tmp);
    }
}
