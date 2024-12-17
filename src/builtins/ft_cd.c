/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:28:42 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/17 17:55:35 by hbouchel         ###   ########.fr       */
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

char	ft_cd(char **env, t_command *cmd)
{
	 char    *path;
    char    oldpwd[PATH_MAX];
    char    pwd[PATH_MAX];

    if (count_arg(cmd->args) > 2)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return env;
    }
    if (!getcwd(oldpwd, PATH_MAX))
    {
        perror("getcwd");
        return env;
    }
    if (!cmd->args[1] || ft_strcmp(cmd->args[1], "~") == 0)
        path = env_value("HOME", env);
    else if (ft_strcmp(cmd->args[1], "-") == 0)
    {
        path = env_value("OLDPWD", env);
        if (!path)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return env;
        }
        printf("%s\n", path);
    }
    else
        path = cmd->args[1];

    if (chdir(path) == -1)
    {
        perror("cd");
        return env;
    }
    env = change_env_value("OLDPWD", env, oldpwd);
    if (getcwd(pwd, PATH_MAX))
        env = change_env_value("PWD", env, pwd);
    else
        perror("getcwd");

    return env;
}
