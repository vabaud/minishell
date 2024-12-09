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

bool	builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if(!ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("echo", cmd, INT_MAX) || (!ft_strncmp("cd", cmd, INT_MAX))
}