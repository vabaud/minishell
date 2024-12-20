/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:16:07 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 11:23:53 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	valid_indentifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	browse_env(char **env, const char *var, char *name, int name_len)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && var[name_len] == '=')
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			free(name);
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_n_up_env(t_all *all, const char *var)
{
	int		i;
	int		name_len;
	char	*name;
	char	**new_env;

	i = 0;
	name_len = 0;
	new_env = NULL;
	while (var[++name_len] && var[name_len] != '=')
		name_len++;
	name = ft_substr(var, 0, name_len);
	if (browse_env(all->env, var, name, name_len))
		return (0);
	new_env = malloc(sizeof(char *) * (count_arg(all->env) + 2));
	while (all->env[i])
	{
		new_env[i] = ft_strdup(all->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free_env(all->env);
	all->env = new_env;
	free(name);
	return (1);
}

void	ft_export(t_all *all, char **args)
{
	int		i;
	char	**new_env;

	new_env = all->env;
	if (count_arg(args) == 1)
	{
		i = -1;
		sort_tab(new_env);
		while (new_env[++i])
			print_var(new_env[i], new_env);
		return ;
	}
	i = 0;
	while (++i < count_arg(args))
	{
		if (valid_indentifier(args[i]))
			add_n_up_env(all, args[i]);
		else
		{
			ft_putstr_fd("export: n'est pas un indentifier valide :",
				STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
	}
}

void	sort_tab(char **env)
{
	int		i;
	int		swapped;
	char	*temp;
	int		count;

	count = count_arg(env);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}
