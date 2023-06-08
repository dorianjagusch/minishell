/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:14:02 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/08 14:06:39 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	child_handler(int sig)
{
	ft_printf("in child handler\n");
	if (sig == SIGINT)
		exit (130);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		exit (131);
	}
	// rl_replace_line("", 1);
	// write(1, "\n", 1);
	// rl_on_new_line();
	// rl_redisplay();
}

void	parent_signal(void)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	s_act.sa_handler = SIG_IGN;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_act, NULL);
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &s_quit, NULL);
}

void	child_signal(void)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	ft_printf("in child signal\n");
	s_act.sa_handler = child_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_act, NULL);
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = child_handler;
	sigaction(SIGQUIT, &s_quit, NULL);
	ft_printf("in child signal last line\n");
}
