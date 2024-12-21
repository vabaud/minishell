/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:14:08 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/21 12:47:05 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_builtins_with_redirection(t_command *cmd, t_all *all,
		t_pipe_info *pipe_info)
{
	int	original_stdin;
	int	original_stdout;

	original_stdin = dup(STDIN_FILENO);
	if (cmd->input_file)
	{
		if (!redirect_input(cmd, pipe_info) || cmd->prev)
		{
            close(original_stdin);
            return ;
		}
	}
	original_stdout = dup(STDOUT_FILENO);
	if (cmd->output_file)
		redirect_output(cmd, pipe_info);
    if(cmd->args && !ft_strcmp(cmd->args[0], "exit"))
    {
        close(original_stdin);
        close(original_stdout);
    }
	execute_builtins(all, cmd, pipe_info);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);
}

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
		{
			execute_builtins_with_redirection(cmd, all, pipe_info);
		}
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
	if (pipe_info->prev_pipe_fd != -1)
		close(pipe_info->prev_pipe_fd);
}

void	execute_pipeline(t_all *all)
{
	t_command	*cmd;
	t_pipe_info	pipe_info;

	pipe_info.prev_pipe_fd = -1;
	pipe_info.i = 0;
	pipe_info.pid = malloc(sizeof(pid_t) * ft_cmdsize(all->cmd));
	pipe_info.pipe_fd[0] = -1;
	pipe_info.pipe_fd[1] = -1;
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
		execute_builtins_with_redirection(cmd, all, pipe_info);
		free_all_exec(all, pipe_info);
		exit(g_exit_code);
	}
	else if (cmd->args && cmd->args[0])
	{
		path = get_path(cmd->args[0], all->env);
		if (!path)
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			g_exit_code = 127;
		}
		else
			execve(path, cmd->args, all->env);
		free(path);
	}
	free_all_exec(all, pipe_info);
	exit(g_exit_code);
}
