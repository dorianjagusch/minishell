/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/15 13:32:56 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "parser.h"
#include "minishell.h"

void	do_child(t_command *head, int *fds, int current, char **env_arr)
{
	size_t		n_cmd;
	t_command	*tmp;

	n_cmd = count_commands(head);
	tmp = set_command(head, current);
	close_fds(fds, current, n_cmd);
	if (dup2(fds[current], STDIN_FILENO) < 0
		|| dup2(fds[current + 1], STDOUT_FILENO) < 0)
		ft_error(0, "");
	close(fds[current]);
	close(fds[current + 1]);
	if (!tmp->command)
		ft_error(NOCMMD, "");
	execve(tmp->command, tmp->params, env_arr);
	ft_error(NOCMMD, tmp->command);
}
