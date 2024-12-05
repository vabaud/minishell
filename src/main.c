/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:26:17 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/03 23:38:07 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void print_env(char **env)
{
    int i = 0;
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
	(void)av;
	if (ac != 1)
		return (0);
    all->env = env_cpy(envp);
	while (1)
	{
		str = readline("!!! shell> ");
		add_history(str);
		if (str[0] == 'p')
			pwd();
		if (!syntax_error_checker(str))
			return (0);
		token = tokenize_input(str);
		all->cmd = parse_token(token, all);
        printf("%s\n", token->value);
	}
	return (0);
}

// test koo sadasd "[wa>""m''esm" < jesj | jesh >> hu
/* Creer un fichier en cas de > et >> */
