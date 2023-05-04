/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 19:01:37 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_child( t_command *head, t_command *command, int current, char **env_arr)
{

	close_fdss(head, current);
	if (dup2(command->fds[0], STDIN_FILENO) < 0
		|| dup2(command->fds[1], STDOUT_FILENO) < 0)
		ft_error(0, "");
	close(command->fds[0]);
	close(command->fds[1]);
	if (!command->command)
	{
		ft_error(NOCMMD, "");
	}
	execve(command->command, command->params, env_arr);
	ft_error(NOCMMD, command->command);
}
