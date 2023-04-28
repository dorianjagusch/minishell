/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/27 09:53:43 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_child(t_cmd *cmds, int current, char *envp[])
{
	close_fds(cmds, current);
	if (dup2(cmds->fd[current][0], STDIN_FILENO) < 0
		|| dup2(cmds->fd[current + 1][1], STDOUT_FILENO) < 0)
		ft_error(0, "");
	close(cmds->fd[current][0]);
	close(cmds->fd[current + 1][1]);
	if (!cmds->cmd[current])
	{
		ft_error(NOCMMD, "");
	}
	ft_print_array(cmds->params[current]);
	execve(cmds->cmd[current], cmds->params[current], envp);
	ft_error(NOCMMD, cmds->cmd[current]);
}
