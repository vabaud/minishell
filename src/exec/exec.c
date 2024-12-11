/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:14:08 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/11 19:20:43 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect_input(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open input");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redirect_output(const char *file, int append_mode)
{
	int	fd;

	if (append_mode)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open output");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	execute_pipeline(t_all *all)
{
	int			pipe_fd[2];
	int			prev_pipe_fd;
	int			pid;
	t_command	*cmd;

	prev_pipe_fd = -1;
	cmd = all->cmd;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->input_file)
				redirect_input(cmd->input_file);
			else if (cmd->prev)
			{
				dup2(prev_pipe_fd, STDIN_FILENO);
				close(prev_pipe_fd);
			}
			if (cmd->output_file)
				redirect_output(cmd->output_file, cmd->append_mode);
			else if (cmd->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			exec_cmd(cmd, all);
			exit(0);
		}
		else
		{
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (cmd->next)
				close(pipe_fd[1]);
			prev_pipe_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
}

void exec_cmd(t_command *cmd, t_all *all)
{
    char *path;

    path = get_path(cmd->args[0], all->env);
    // if (is_bultin(cmd))
    //     exec_builtin(cmd, all);
    // else
    // {
    execve(path, cmd->args, all->env);
    // }
}
