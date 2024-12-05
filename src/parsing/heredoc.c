/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:45:04 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/05 20:44:09 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(t_command *cmd, t_token *token, t_all *all)
{
	char	*delimiter;
	char	*line;
	int		change;
	int		fd;

	change = 0;
	fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    cmd->input_file = ft_strdup("/tmp/heredoc.tmp");
	delimiter = remove_quotes(token->next->value);
	if (ft_strcmp(delimiter, token->next->value))
		change = 1;
	while (1)
	{
        line = readline("> ");
        if (!ft_strcmp(delimiter, line))
            break;
        if (change == 1)
            line = replace_env(line, all);
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
	}
    close(fd);
    free(delimiter);
}
