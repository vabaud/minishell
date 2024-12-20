/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:29:40 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 11:29:40 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**path_tab;
	char	*full_path;
	char	*cmd_path;

	i = -1;
	if (cmd[0] == '/' && access(cmd, X_OK) == 0)
	{
		return (ft_strdup(cmd));
	}
	full_path = env_value(ft_strdup("PATH"), env);
	if (!full_path)
		return (NULL);
	path_tab = ft_split(full_path, ':');
	free(full_path);
	while (path_tab[++i])
	{
		full_path = ft_strjoin(path_tab[i], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (free_env(path_tab), cmd_path);
		free(cmd_path);
	}
	return (free_env(path_tab), NULL);
}
