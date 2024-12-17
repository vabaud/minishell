/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:53:23 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/17 16:01:29 by vabaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_received_signal = 130;
		write(1, "\n", 1);
	}
}

void handle_sigint(int signal)
{
    (void)signal;
    g_received_signal = 130;
    write(STDERR_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	handle_sigquit(int signal)
{
	(void)signal;
	g_received_signal = 131;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_sigint(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
}

void setup_interactive_signals()
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	// sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
}

void setup_child_process_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}