/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:42 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/17 18:06:14 by hbouchel         ###   ########.fr       */
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

char **	ft_cd(char **env, t_command *cmd)
{
	char    *path;
    char    oldpwd[PATH_MAX];
    char    pwd[PATH_MAX];

    if (count_arg(cmd->args) > 2)
        return (fprintf(stderr, "cd: too many arguments\n"), env);
    if (!getcwd(oldpwd, PATH_MAX))
        return (perror("getcwd"), env);
    if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
        path = env_value("HOME", env);
    else if (ft_strcmp(cmd->args[1], "-") == 0)
    {
        if (!(path = env_value("OLDPWD", env)))
            return (fprintf(stderr, "cd: OLDPWD not set\n"), env);
        printf("%s\n", path);
    }
    else
        path = cmd->args[1];
    if (chdir(path) == -1)
        return (perror("cd"), env);
    env = change_env_value("OLDPWD", env, oldpwd);
    if (getcwd(pwd, PATH_MAX))
        env = change_env_value("PWD", env, pwd);
    return env;
}
