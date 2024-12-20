/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:56:15 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/20 13:15:55 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect_input(t_command *cmd, int prev_pipe_fd)
{
	int	fd;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("open input");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (cmd->prev)
	{
		dup2(prev_pipe_fd, STDIN_FILENO);
		close(prev_pipe_fd);
	}
}

void	redirect_output(t_command *cmd, int *pipe_fd)
{
	int	fd;

	if (cmd->output_file)
	{
		if (cmd->append_mode)
			fd = open(cmd->output_file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(cmd->output_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open output");
			exit(EXIT_FAILURE);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

int	parent_process(int prev_pipe_fd, int *pipe_fd, t_command *cmd)
{
	if (prev_pipe_fd != -1)
		close(prev_pipe_fd);
	if (cmd->next)
		close(pipe_fd[1]);
	prev_pipe_fd = pipe_fd[0];
	return (prev_pipe_fd);
}

void	free_all_exec(t_all *all, pid_t *pid)
{
	free_cmd(all->cmd);
	free_env(all->env);
	free(all);
	free(pid);
}
