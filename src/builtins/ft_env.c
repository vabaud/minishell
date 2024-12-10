/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:41 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/10 16:25:44 by hbouchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(char **env, t_command *cmd)
{
	int	i;

	i = 0;
	if (count_arg(cmd->args))
	{
		while (env[i])
		{
			ft_printf("%s\n", env[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
