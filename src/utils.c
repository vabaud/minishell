/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:10:32 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 17:34:14 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cmdsize(t_command *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

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
        {
			new_str = ft_strcharadd(new_str, s[i]);
            i++;
        }
	}
	free(s);
	return (new_str);
}

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
