/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:26:17 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/18 19:01:32 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		printf("%s\n", path);
		return (1);
	}
	return (0);
}

int	main(void)
{
	char	*str;

	while (1)
	{
		str = readline("!!! shell> ");
		if (str[0] == 'p')
			pwd();
        if (!syntax_error_checker(str))
            return 0;
        tokenize_input(str);
		add_history(str);
		printf("%s\n", str);
	}
}
