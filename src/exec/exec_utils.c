/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:56:15 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/21 11:42:02 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_input(t_command *cmd, t_pipe_info *pipe_info)
{
	int	fd;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("open input");
			g_exit_code = EXIT_FAILURE;
			return (0);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (pipe_info->prev_pipe_fd != -1)
		{
			close(pipe_info->prev_pipe_fd);
			pipe_info->prev_pipe_fd = -1;
		}
	}
	else if (cmd->prev)
	{
		dup2(pipe_info->prev_pipe_fd, STDIN_FILENO);
		close(pipe_info->prev_pipe_fd);
	}
	return (1);
}

void	redirect_output(t_command *cmd, t_pipe_info *pipe_info)
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
		if (pipe_info->pipe_fd[1] != -1)
		{
			close(pipe_info->pipe_fd[1]);
			close(pipe_info->pipe_fd[0]);
		}
	}
	else if (cmd->next)
	{
		dup2(pipe_info->pipe_fd[1], STDOUT_FILENO);
		close(pipe_info->pipe_fd[0]);
		close(pipe_info->pipe_fd[1]);
	}
}

void	parent_process(t_pipe_info *pipe_info, t_command *cmd)
{
	if (pipe_info->prev_pipe_fd != -1)
		close(pipe_info->prev_pipe_fd);
	if (cmd->next)
	{
		close(pipe_info->pipe_fd[1]);
	}
	pipe_info->prev_pipe_fd = pipe_info->pipe_fd[0];
}

void	free_all_exec(t_all *all, t_pipe_info *pipe_info)
{
	free_cmd(all->cmd);
	free_env(all->env);
	free(all);
	free(pipe_info->pid);
}
