/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:14:08 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/20 16:04:47 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_children(t_pipe_info *pipe_info)
{
	int	j;
	int	status;

	status = 0;
	j = 0;
	while (j < pipe_info->i)
	{
		waitpid(pipe_info->pid[j], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_code = 128 + WTERMSIG(status);
		j++;
	}
}

void	pipe_loop(t_command *cmd, t_all *all, t_pipe_info *pipe_info)
{
	while (cmd)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_sigint_cmd);
		if (cmd->next)
			pipe(pipe_info->pipe_fd);
		if (is_builtin(cmd) && !cmd->prev && !cmd->next)
			execute_builtins(all, cmd, pipe_info);
		else
		{
			pipe_info->pid[pipe_info->i] = fork();
			if (pipe_info->pid[pipe_info->i++] == 0)
			{
				redirect_input(cmd, pipe_info);
				exec_cmd(cmd, all, pipe_info);
			}
			else
				parent_process(pipe_info, cmd);
		}
		cmd = cmd->next;
	}
}

void	execute_pipeline(t_all *all)
{
	t_command	*cmd;
	t_pipe_info	pipe_info;

	pipe_info.prev_pipe_fd = -1;
	pipe_info.i = 0;
	pipe_info.pid = malloc(sizeof(pid_t) * ft_cmdsize(all->cmd));
	cmd = all->cmd;
	pipe_loop(cmd, all, &pipe_info);
	if (!is_builtin(all->cmd) || (is_builtin(all->cmd) && all->cmd->next))
		wait_children(&pipe_info);
	init_signals();
	free(pipe_info.pid);
}

void	exec_cmd(t_command *cmd, t_all *all, t_pipe_info *pipe_info)
{
	char	*path;

	redirect_output(cmd, pipe_info);
	if (is_builtin(cmd))
	{
		execute_builtins(all, cmd, pipe_info);
		free_all_exec(all, pipe_info);
	}
	else
	{
		path = get_path(cmd->args[0], all->env);
		if (!path)
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			g_exit_code = 127;
			free_all_exec(all, pipe_info);
		}
		else
			execve(path, cmd->args, all->env);
		free(path);
	}
	exit(g_exit_code);
}
