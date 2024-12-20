/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:26:17 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 10:51:18 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_exit_code = 0;

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	shell_loop(t_all *all, t_token *token)
{
	char	*str;

	while (1)
	{
		str = readline("!!! shell> ");
		if (!str)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (str[0] != '\0')
		{
			add_history(str);
			if (syntax_error_checker(str))
			{
				token = tokenize_input(str);
				if (syntax_token(token))
				{
					all->cmd = parse_token(token, all);
					execute_pipeline(all);
					free_cmd(all->cmd);
				}
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_token	*token;
	t_all	*all;

	token = NULL;
	all = malloc(sizeof(t_all));
	(void)av;
	if (ac != 1)
		return (0);
	init_signals();
	all->env = env_cpy(envp);
	shell_loop(all, token);
	free_env(all->env);
	free(all);
	return (0);
}
