/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:26:17 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/11 22:11:11 by vabaud           ###   ########.fr       */
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
        if (has_unclosed_quotes(str))
            printf("unclosed quotes\n");
        if (has_logical_operators(str))
            printf("logical operator \"&&\" and \"||\" are not supported\n");
        if (has_invalid_redirections(str))
            printf("invalid redirections\n");
		add_history(str);
		printf("%s\n", str);
	}
}
