/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:14:02 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/09 17:28:06 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	child_handler(int sig)
{
	(void)sig;
	return ;
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

	s_act.sa_handler = child_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_RESTART;
	sigaction(SIGINT, &s_act, NULL);
	sigemptyset(&s_quit.sa_mask);
	s_quit.sa_handler = child_handler;
	sigaction(SIGQUIT, &s_quit, NULL);
}
