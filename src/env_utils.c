/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:32:42 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 17:05:24 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*replace_env(char *s, t_all *all)
{
	int		i;
	int		start;
	char	*str;
	char	*env;

	i = 0;
	start = 0;
	str = NULL;
	while (s[i])
	{
		if (s[i] == '$' && !in_s_quote(s, i))
		{
			s[i++] = 'a';
			start = i;
			while (ft_isalnum(s[i]) || s[i] == '_')
				i++;
			env = env_value(ft_substr(s, start, i - start), all->env);
			if (s[i] && env[0] == '\0' && s[i++] == '?')
				env = ft_itoa(g_exit_code);
			str = ft_strjoin_and_free(str, env);
		}
		else if (s[i] != '\0')
			str = ft_strcharadd(str, s[i++]);
	}
	return (free(s), str);
}

char	*env_value(char *s, char **env_tab)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	env = NULL;
	while (env_tab[i])
	{
		j = 0;
		while (env_tab[i][j] && env_tab[i][j] != '=')
			j++;
		if (!ft_strncmp(env_tab[i], s, j))
		{
			j++;
			env = ft_substr(env_tab[i], j, ft_strlen(env_tab[i]) - 1);
		}
		i++;
	}
	if (env == NULL)
		env = "\0";
	free(s);
	return (env);
}

char	**change_env_value(char *env, char **env_tab, char *value)
{
	int		i;
	int		j;
	char	*tmp;
	char	**new_env;

	i = 0;
	j = 0;
	tmp = NULL;
	while (env_tab[i])
	{
		j = 0;
		while (env_tab[i][j] && env_tab[i][j] != '=')
			j++;
		if (!ft_strncmp(env_tab[i], env, j))
		{
			tmp = ft_substr(env_tab[i], 0, j + 1);
			free(env_tab[i]);
			env_tab[i] = ft_strjoin(tmp, value);
			free(tmp);
		}
		i++;
	}
	new_env = env_cpy(env_tab);
	free_env(env_tab);
	return (new_env);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
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
