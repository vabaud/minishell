/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:42 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/17 15:42:12 by vabaud           ###   ########.fr       */
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

void	ft_cd(char **env, t_command *cmd)
{
	char	*path;
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];

	path = NULL;
	getcwd(oldpwd, PATH_MAX);
	if (count_arg(cmd->args) > 2)
		return ;
	if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
		path = env_value("HOME", env);
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
		return ;
    printf("%s\n", path);
	env = change_env_value("OLDPWD", env, oldpwd);
	getcwd(pwd, PATH_MAX);
	env = change_env_value("PWD", env, pwd);
}
