/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabaud <vabaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:53:23 by vabaud            #+#    #+#             */
/*   Updated: 2024/12/16 18:52:33 by vabaud           ###   ########.fr       */
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
