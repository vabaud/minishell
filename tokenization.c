/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:13:26 by vabaud            #+#    #+#             */
/*   Updated: 2024/11/15 18:38:40 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int tokenize_input(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if(ft_strchr("><|", s[i]))
            i = handle_special_chars(*s, i);
        else
            i = handle_word(*s);
        i++;
    }
    return 0;
}

int handle_special_chars(char *s, int i)
{
    if (s[i++] == '>')
    {
        if (s[i] == '>')
            token = TOKEN_REDIR_APPEND;
        else
            token = TOKEN_REDIR_OUT;
    }
    else if (s[i++] == '<')
    {
        if (s[i] == '<')
            token = TOKEN_REDIR_HEREDOC;
        else
            token = TOKEN_REDIR_IN;
    }
    else if (s[i++] == '|')
        token = TOKEN_PIPE;
    return (i);
}
// handle_word
// print_tokens
