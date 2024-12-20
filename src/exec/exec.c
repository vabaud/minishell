/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:14:08 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/20 12:05:29 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	wait_children(pid_t *pids, int i)
{
	int	j;
	int	status;

	status = 0;
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_code = 128 + WTERMSIG(status);
		j++;
	}
}

void	pipe_loop(t_command *cmd, t_all *all, pid_t *pid, int prev_pipe_fd)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	while (cmd)
	{
		signal(SIGQUIT, handle_sigquit);
		signal(SIGINT, handle_sigint_cmd);
		if (cmd->next)
			pipe(pipe_fd);
		if (is_builtin(cmd) && !cmd->prev && !cmd->next)
			execute_builtins(all, cmd, pid);
		else
		{
			pid[i] = fork();
			if (pid[i++] == 0)
			{
				redirect_input(cmd, prev_pipe_fd);
				exec_cmd(cmd, all, pid, pipe_fd);
			}
			else
				parent_process(prev_pipe_fd, pipe_fd, cmd);
		}
		cmd = cmd->next;
	}
}

void	execute_pipeline(t_all *all)
{
	int			prev_pipe_fd;
	t_command	*cmd;
	pid_t		*pid;

	prev_pipe_fd = -1;
	cmd = all->cmd;
	pid = malloc(sizeof(pid_t) * ft_cmdsize(all->cmd));
	pipe_loop(cmd, all, pid, prev_pipe_fd);
	if (!is_builtin(all->cmd) || (is_builtin(all->cmd) && all->cmd->next))
		wait_children(pid, ft_cmdsize(all->cmd));
	init_signals();
	free(pid);
}

void	exec_cmd(t_command *cmd, t_all *all, pid_t *pid, int *pipe_fd)
{
	char	*path;

	redirect_output(cmd, pipe_fd);
	if (is_builtin(cmd))
	{
		execute_builtins(all, cmd, pid);
		free_all_exec(all, pid);
	}
	else
	{
		path = get_path(cmd->args[0], all->env);
		if (!path)
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			g_exit_code = 127;
			free_all_exec(all, pid);
		}
		else
			execve(path, cmd->args, all->env);
		free(path);
	}
	exit(g_exit_code);
}
