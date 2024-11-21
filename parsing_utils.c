/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:02:04 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/20 16:19:57 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_command	*new_command()
{
	t_command	*cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;
    cmd->args = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_mode = 0;
    cmd->next = NULL;

	return (cmd);
}
