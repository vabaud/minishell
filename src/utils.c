/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:10:32 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/19 18:43:36 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmdsize(t_command *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*remove_quotes(char *s)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	while (s[i])
	{
		while (!in_quotes(s[i]) && (s[i] == '\'' || s[i] == '\"'))
		{
			i++;
		}
		if (s[i])
			new_str = ft_strcharadd(new_str, s[i++]);
	}
	free(s);
	return (new_str);
}

char	**env_cpy(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
    new_env[i] = NULL;
	return (new_env);
}
