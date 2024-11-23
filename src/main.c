/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:26:17 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/23 18:53:56 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*str;
    t_token *token;

    token = NULL;
	while (1)
	{
		str = readline("!!! shell> ");
		add_history(str);
		if (str[0] == 'p')
			pwd();
        if (!syntax_error_checker(str))
            return 0;
        token = tokenize_input(str);
        parse_token(token);
        str = remove_quotes(str);
		ft_printf("%s\n", str);
	}
}

// test koo sadasd "[wa>""m''esm" < jesj | jesh >> hu
/* Creer un fichier en cas de > et >> */
