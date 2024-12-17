/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:25:24 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/17 19:57:58 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(t_command *cmd)

{
	int i;
	int newline;

	i = 1;       // debuter apres echo
	newline = 0; // saut de ligne active par defaut

	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (cmd->args[i])
	{
        while (i > 2 && i < (count_arg(cmd->args) - 1) && !ft_strncmp(cmd->args[i], "-n", 2))
            i++;
		ft_printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!newline)
		ft_printf("\n");
}
