/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:16:38 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/20 15:30:50 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtins(t_all *all, t_command *cmd, t_pipe_info *pipe_info)
{
	if (!cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd), 1);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_cd(all, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(all, cmd->args), 1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(all, cmd->args), 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(all->env, cmd), 1);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd->args, all, pipe_info->pid), 1);
	return (0);
}
