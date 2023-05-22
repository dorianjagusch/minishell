/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/22 16:21:23 by djagusch         ###   ########.fr       */
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
	while (pipe < n_cmd << 1)
	{
		if (!(cur == 0 && pipe == 0)
			&& !(cur + 1 == n_cmd && pipe == (n_cmd << 1) - 1)
			&& !((pipe == (cur << 1) - 1 || pipe == ((cur + 1) << 1))
				&& cur != n_cmd))
		{
			if (cur == 1)
				printf("closing fd %d\n", pipe);
			close(fds[pipe]);
		}
		pipe++;
	}
}
