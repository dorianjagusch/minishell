/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/17 13:09:59 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (pipe <= n_cmd)
	{
		if (pipe != cur && pipe != n_cmd)
		{
			ft_printf("closed reading FD %d in position %d for command %d\n",
				fds[pipe], pipe, cur);
			close(fds[cur + 0]);
		}
		if (pipe != cur + 1 && pipe != 0)
		{
			ft_printf("closed writing FD %d in position %d for command %d\n",
				fds[pipe], pipe, cur);
			close(fds[cur + 1]);
		}
		pipe++;
	}
}
