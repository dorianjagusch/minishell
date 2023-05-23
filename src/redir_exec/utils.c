/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/23 20:32:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/time.h>

void	close_command_pipes(t_command *command)
{
	t_command	*tmp;

	tmp = command;
	while (tmp)
	{
		close(tmp->fds[0]);
		close(tmp->fds[1]);
		tmp = tmp->next;
	}
}

void	close_fds(int *fds, int cur, int n_cmd)
{
	int	pipe;

	pipe = 0;
	while (pipe < n_cmd)
	{	
		if (pipe != (cur << 1) && cur != n_cmd  - 1)
			close(fds[pipe]);
		if (pipe + 3 != (((cur + 1) << 1) + 1) && cur != 0)
			close(fds[pipe + 2]);
		pipe += 2;
	}
}
