/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:42 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/21 14:19:50 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

int	ft_cd(t_all *all, t_command *cmd)
{
	char	*path;
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];

	path = NULL;
	getcwd(oldpwd, PATH_MAX);
	if (count_arg(cmd->args) > 2)
		return (ft_putstr_fd("Too many arguments\n", STDERR_FILENO), 1);
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		path = env_value(ft_strdup("HOME"), all->env);
	else
		path = ft_strdup(cmd->args[1]);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	free(path);
	all->env = change_env_value("OLDPWD", all->env, oldpwd);
	getcwd(pwd, PATH_MAX);
	all->env = change_env_value("PWD", all->env, pwd);
	return (0);
}
