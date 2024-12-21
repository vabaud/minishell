/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:15:52 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/21 14:37:44 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_var(char *env, char **env_tab)
{
	char	*value;
	char	*new_env;
	int		i;

	i = -1;
	new_env = NULL;
	value = NULL;
	while (env[++i] && env[i] != '=')
		new_env = ft_strcharadd(new_env, env[i]);
	if (env[i] == '=')
	{
		value = env_value(ft_strdup(new_env), env_tab);
		ft_printf("declare -x %s=\"%s\"\n", new_env, value);
		free(value);
	}
	else
		ft_printf("declare -x %s\n", new_env);
	free(new_env);
}

void	print_err_export(char *args)
{
	ft_putstr_fd("export: n'est pas un indentifier valide :", STDERR_FILENO);
	ft_putstr_fd(args, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
