/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:10:32 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/25 14:58:17 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_quotes(char *s)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = NULL;
	while (s[i])
	{
		while (!in_quotes(s[i]) && (s[i] == '\'' || s[i] == '\"'))
		{
			i++;
		}
		if (s[i])
			new_str = ft_strcharadd(new_str, s[i++]);
	}
	free(s);
	return (new_str);
}
