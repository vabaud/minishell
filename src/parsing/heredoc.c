/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:45:04 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/19 19:47:16 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(t_command *cmd, t_token *token, t_all *all)
{
	char	*delimiter;
	char	*line = NULL;
	int		change;
	int		fd;

	change = 0;
	fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (cmd->input_file)
        free(cmd->input_file);
    cmd->input_file = ft_strdup("/tmp/heredoc.tmp");
	delimiter = remove_quotes(ft_strdup(token->next->value));
    printf("%s\n", token->next->value);
	if (ft_strcmp(delimiter, token->next->value))
		change = 1;
	while (1)
	{
        ft_putstr_fd("> ", STDOUT_FILENO);
        line = get_next_line(STDIN_FILENO);
        if (!line)
        {
            write(1, "Heredoc: EOF detected\n", 23);
            free(line);
            break;
        }
        line[ft_strlen(line) - 1] = '\0';
        if (!ft_strcmp(delimiter, line))
        {
            free(line);
            break;
        }
        if (change == 1)
        {
            free(line);
            line = replace_env(line, all);
        }
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
	}
    close(fd);
    free(delimiter);
}
