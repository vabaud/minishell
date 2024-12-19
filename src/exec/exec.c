/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:14:08 by hbouchel          #+#    #+#             */
/*   Updated: 2024/12/19 19:09:26 by vabaud           ###   ########.fr       */
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
	t_command	*cmd;
    pid_t *pid;
    int i = 0;

	prev_pipe_fd = -1;
	cmd = all->cmd;
    pid = malloc(sizeof(pid_t) * ft_cmdsize(all->cmd));
	while (cmd)
	{
        if (isatty(0))
            signal(SIGQUIT, handle_sigquit);
        signal(SIGINT, handle_sigint_cmd);
		if (cmd->next)
			pipe(pipe_fd);
        if (is_builtin(cmd) && !cmd->prev && !cmd->next)
            execute_builtins(all, cmd, pid);
        else
        {
            pid[i] = fork();
            if (pid[i] == 0)
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
                exec_cmd(cmd, all, pid);
            }
            else
            {
                if (prev_pipe_fd != -1)
                    close(prev_pipe_fd);
                if (cmd->next)
                    close(pipe_fd[1]);
                prev_pipe_fd = pipe_fd[0];
            }
        }
		cmd = cmd->next;
        i++;
	}
    if (!is_builtin(all->cmd) || (is_builtin(all->cmd) && all->cmd->next))
        wait_children(pid, i);
    init_signals();
    free(pid);
}

void exec_cmd(t_command *cmd, t_all *all, pid_t *pid)
{
    char *path;

    if (is_builtin(cmd))
    {
        execute_builtins(all, cmd, pid);
        free_cmd(all->cmd);
        free_env(all->env);
        free(all);
        free(pid);
    }
    else
    {
        path = get_path(cmd->args[0], all->env);
        if (!path)
        {
            ft_putstr_fd("command not found\n", STDERR_FILENO);
            free_cmd(all->cmd);
            free_env(all->env);
            free(all);
            free(pid);
            g_exit_code = 127;
        }
        else
            execve(path, cmd->args, all->env);
        free(path);
    }
    exit(g_exit_code);
}
