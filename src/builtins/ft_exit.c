/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbouchel <hbouchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:51:16 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/09 21:02:53 by hbouchel         ###   ########.fr       */
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

void	ft_exit(char **args)
{
	int i = 0;

	ft_putstr_fd("exit\n", STDOUT_FILENO);

	if(args[1])
	{
		if(val_numb(args[1]))
		{
			i = atoi(args[1]);
			if(args[2])
			{
				ft_putstr_fd("exit, trop d'arguemnts\n", STDOUT_FILENO);
				return;
			}
			exit(i);
		}
		else
		{
			ft_putstr_fd("exit: requiert un argument numerique\n", STDOUT_FILENO);
			exit(255);
		}
	}
	exit(0);
}