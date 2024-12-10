/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:32:42 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/10 12:32:56 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	in_s_quote(char *s, int i)
{
	int	j;
	int	q_char;

	j = 0;
	q_char = 0;
	while (j < i)
	{
		if (s[j] == '"' || s[j] == '\'')
		{
			if (q_char == s[j])
				q_char = 0;
			else if (q_char == 0)
				q_char = s[j];
		}
		j++;
	}
	if (q_char == '\'')
		return (1);
	return (0);
}

char	*replace_env(char *s, t_all *all)
{
	int		i;
	int		start;
	char	*str;
	char	*env;

	i = 0;
	start = 0;
	str = NULL;
	env = NULL;
	while (s[i])
	{
		if (s[i] == '$' && !in_s_quote(s, i))
		{
			s[i++] = 'a';
			start = i++;
			while (ft_isalnum(s[i]))
				i++;
			env = env_value(ft_substr(s, start, i - start), all->env);
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
		while (env_tab[i][j] != '=')
			j++;
		if (!ft_strncmp(env_tab[i], s, j))
		{
			j++;
			env = ft_substr(env_tab[i], j, ft_strlen(env_tab[j]) - 1);
		}
		i++;
	}
	if (env == NULL)
		env = "\0";
	// if (s)
		// free(s);
	return (env);
}

char	**change_env_value(char *env, char **env_tab, char *value)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = NULL;
	while (env_tab[i])
	{
		j = 0;
		while (env_tab[i][j] != '=')
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
	return (env_tab);
}
