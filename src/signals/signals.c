/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:14:02 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/07 14:35:54 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		g_info.exit_value = 1;
	}
}

void	global_signal(int toggle)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	if (toggle == ON)
	{
		s_act.sa_handler = sigint_handler;
		sigemptyset(&s_act.sa_mask);
		s_act.sa_flags = SA_RESTART;
		sigaction(SIGINT, &s_act, NULL);
	}
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_quit, NULL);
}

static	void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
		exit (1);
}

void	heredoc_signal(void)
{
	struct sigaction	s_act;

	s_act.sa_handler = heredoc_handler;
	sigemptyset(&s_act.sa_mask);
	sigaction(SIGINT, &s_act, NULL);
	sigaction(SIGTSTP, &s_act, NULL);
}
