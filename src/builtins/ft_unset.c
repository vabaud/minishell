/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:16:11 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 11:16:23 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_env(t_all *all, char *s)
{
	int		i;
	int		j;
	int		k;
	char	**new_env;

	k = 0;
	i = 0;
	j = 0;
	while (all->env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	while (all->env[i])
	{
		j = 0;
		while (all->env[i][j] != '=')
			j++;
		if (ft_strncmp(all->env[i], s, j))
			new_env[k++] = ft_strdup(all->env[i]);
		i++;
	}
	new_env[k] = NULL;
	free_env(all->env);
	all->env = new_env;
}

int	ft_unset(t_all *all, char **args)
{
	int	i;

	if (!args || !args[0])
	{
		ft_putstr_fd("unset: pas assez d'arguments\n", STDOUT_FILENO);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		remove_env(all, args[i]);
		i++;
	}
	return (1);
}
