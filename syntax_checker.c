/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:25:48 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/11 22:44:46 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// syntax_error_checker
// has_misplaced_operators

int	has_unclosed_quotes(char *s)
{
	int i;
	char t_quote;

	i = 0;
    t_quote = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && s[i-1] != '\\')
        {
            if (s[i] == t_quote)
                t_quote = 0;
            else if (t_quote == 0)
                t_quote = s[i];
        }
		i++;
	}
	if (t_quote != 0)
		return (1);
	return (0);
}

int has_logical_operators(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if ((s[i] == '&' && s[i+1] == '&') || (s[i] == '|' && s[i+1] == '|'))
            return 1;
        i++;
    }
    return 0;
}

int has_invalid_redirections(char *s)
{
    int start;
    int end;

    start = 0;
    end = ft_strlen(s) - 1;
    while ((s[start] == ' ' || s[start] == '\t') && s[start] != '\0')
        start++;
    while ((s[end] == ' ' || s[end] == '\t') && end > 0)
        end--;
    if (s[start] == '>' || s[start] == '<' || s[end] == '>' || s[end] == '<')
        return 1;
    while (s[start])
    {
        if ((s[start] == '>' || s[start] == '<') && (s[start+1] == '>' || s[start+1] == '<') && (s[start+2] == '>' || s[start+2] == '<'))
            return 1;
        if ((s[start] == '>' || s[start] == '<') && (s[start+1] == ' ' || s[start+1] == '\t'))
        {
            while ((s[++start] == ' ' || s[start] == '\t') && s[start] != '\0')
                ;
            if (s[start] == '<' || s[start] == '>')
                return 1;
        }
        start++;
    }
    return 0;
}


