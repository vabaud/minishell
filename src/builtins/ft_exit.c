/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:51:16 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/21 12:35:00 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	val_numb(const char *str)
{
	if (!str || *str == '\0')
	{
		return (0);
	}
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(char **args, t_all *all, t_pipe_info *pipe_info, t_command *cmd)
{
	int	i;

	i = 0;
    if (!cmd->prev)
    {    
        ft_putstr_fd("exit\n", STDOUT_FILENO);
    }
	if (args[1])
	{
		if (val_numb(args[1]))
		{
			i = atoi(args[1]);
			if (args[2])
				return (ft_putstr_fd("exit, trop d'arguemnts\n",
						STDERR_FILENO));
		}
		else
		{
			ft_putstr_fd("exit: requiert un argument numerique\n",
				STDERR_FILENO);
			i = 255;
		}
	}
	free_all_exec(all, pipe_info);
	exit(i);
}
