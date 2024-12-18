/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:32:42 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/18 19:17:11 by vabaud           ###   ########.fr       */
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
	while (s[i])
	{
		if (s[i] == '$' && !in_s_quote(s, i))
		{
			s[i++] = 'a';
			start = i;
			while (ft_isalnum(s[i]) || s[i] == '_')
				i++;
			env = env_value(ft_substr(s, start, i - start), all->env);
            if (env[0] == '\0' && s[i++] == '?')
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
		while (env_tab[i][j] != '=')
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
	// if (s)
		// free(s);
	return (env);
}

char	**change_env_value(char *env, char **env_tab, char *value)
{
	int		i;
	int		j;
	char	*tmp;
    char **new_env;

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
    new_env = env_cpy(env_tab);
    free_env(env_tab);
	return (new_env);
}

void free_env(char **env)
{
    int i = 0;

    if (!env)
        return;
    while (env[i])
    {
        free(env[i]);
        i++;
    }
    free(env);
}

void add_env(t_all *all, char *s)
{
    int i = 0;
    char **new_env;
    new_env = malloc(sizeof(char *) * (count_arg(all->env) + 2));
    while (all->env[i])
    {
        new_env[i] = ft_strdup(all->env[i]);
        i++;
    }
    new_env[i] = ft_strdup(s);
    new_env[i] = NULL;
    free_env(all->env);
    all->env = new_env;
}
