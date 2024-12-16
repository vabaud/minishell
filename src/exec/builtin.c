/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:16:38 by hbouchel          #+#    #+#             */
/*   Updated: 2024/11/25 16:27:31 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int execute_builtins(t_all *all, t_command *cmd)
{
    if (!cmd->args[0])
        return (0);

    if (ft_strcmp(cmd->args[0], "echo") == 0)
        return (ft_echo(cmd->args), 1);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
        return (ft_cd(all, cmd->args), 1);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        return (ft_pwd(), 1);
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        return (ft_export(cmd->args, &all->env), 1);
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        return (ft_unset(cmd->args, &all->env), 1);
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        return (ft_env(all->env));
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        return (ft_exit(cmd->args), 1);

    return (0);
}