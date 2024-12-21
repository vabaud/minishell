/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:16:38 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/21 14:41:53 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
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

void	execute_builtins(t_all *all, t_command *cmd, t_pipe_info *pipe_info)
{
	if (!cmd->args || !cmd->args[0])
		return ;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		g_exit_code = ft_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		g_exit_code = ft_cd(all, cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		g_exit_code = ft_pwd();
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		g_exit_code = ft_export(all, cmd->args);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		g_exit_code = ft_unset(all, cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		g_exit_code = ft_env(all->env, cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args, all, pipe_info, cmd);
}
