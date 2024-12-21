/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:45:04 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/21 14:58:58 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_handler(int signal)
{
	(void)signal;
	g_exit_code = 130;
	write(STDERR_FILENO, "\n", 1);
}

void	heredoc_loop(char *delimiter, int change, int fd, t_all *all)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_exit_code == 130)
		{
			write(1, "Heredoc: EOF detected\n", 23);
			break ;
		}
		if (line[0] && not_only_space(line))
		{
			line[ft_strlen(line) - 1] = '\0';
			if (!ft_strcmp(delimiter, line))
				return (free(line));
			if (change == 0)
				line = replace_env(line, all);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
		}
		free(line);
	}
}

void	handle_heredoc(t_command *cmd, t_token *token, t_all *all)
{
	char	*delimiter;
	int		change;
	int		fd;

	change = 0;
	fd = open("/tmp/heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = ft_strdup("/tmp/heredoc.tmp");
	delimiter = remove_quotes(ft_strdup(token->next->value));
	sigaction_handle();
	if (ft_strcmp(delimiter, token->next->value))
		change = 1;
	heredoc_loop(delimiter, change, fd, all);
	close(fd);
	free(delimiter);
	signal(SIGINT, handle_sigint);
}
