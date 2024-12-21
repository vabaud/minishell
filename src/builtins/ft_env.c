/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:41 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/21 12:56:18 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **env, t_command *cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (count_arg(cmd->args))
	{
		while (env[i])
		{
			j = 0;
			while (env[i][j] && env[i][j] != '=')
				j++;
			if (env[i][j] == '=')
				ft_printf("%s\n", env[i]);
			i++;
		}
		return (1);
	}
	ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
	return (0);
}
