/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:26:17 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/12 16:00:12 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_received_signal = 0;

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

int	main(int ac, char **av, char **envp)
{
	char	*str;
	t_token	*token;
	t_all	*all;

	token = NULL;
	all = malloc(sizeof(t_all));
    all->exit_code = 0;
	(void)av;
	if (ac != 1)
		return (0);
    init_signals();
	all->env = env_cpy(envp);
	while (1)
	{
		str = readline("!!! shell> ");
        if (!str || str[0] == '\0')
        {
            write(1, "exit\n", 5);
            break;
        }
		add_history(str);
		if (!syntax_error_checker(str))
			return (0);
		token = tokenize_input(str);
		all->cmd = parse_token(token, all);
        execute_pipeline(all);
	}
	return (0);
}

// test koo sadasd "[wa>""m''esm" < jesj | jesh >> hu
