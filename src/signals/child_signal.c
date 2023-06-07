/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:14:02 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/07 14:57:38 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	child_handler(int sig)
{
	if (sig == SIGINT)
		exit (CTRL_EXIT);
	if (sig == SIGQUIT)
	{
		write(1, "Quit: 3", 7);
		exit (BSLASH_EXIT);
	}
}

void	child_signal(void)
{
	struct sigaction	s_act;
	struct sigaction	s_quit;

	s_act.sa_handler = child_handler;
	sigemptyset(&s_act.sa_mask);
	sigaction(SIGINT, &s_act, NULL);
	s_quit.sa_handler = child_handler;
	sigemptyset(&s_quit.sa_mask);
	sigaction(SIGQUIT, &s_quit, NULL);
	sigaction(SIGTSTP, &s_quit, NULL);
}
