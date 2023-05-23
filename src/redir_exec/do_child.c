/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/23 20:37:08 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "parser.h"
#include "minishell.h"

int	dup_fds(int *fds, int n_cmd, int current)
{
	if (dup2(fds[(current << 1)], STDIN_FILENO) < 0)
	{
		ft_error(0, "34frfdyf");
		return (EPIPE);
	}
	if (dup2(fds[((current + 1) << 1) + 1], STDOUT_FILENO) < 0)
	{
		ft_error(0, "34ff7uuk67ijhgrujnyby");
		return (EPIPE);
	}
	if (current != n_cmd - 1)
		close(fds[(current << 1)]);
	if (current != 0)
		close(fds[((current + 1) << 1) + 1]);
	return (0);
}

int	do_child(t_command *command, int *fds, int n_cmd, t_env *env)
{
	int			current;
	char		**env_arr;

	current = command->id;
	close_fds(fds, current, n_cmd);
	printf("Here2\n");
	dup_fds(fds, n_cmd, current);
	if (!command->command)
		ft_error(NOCMMD, "");
	if (exec_builtin(&env, command))
	{
		env_arr = ft_env_to_array(env);
		close_command_pipes(command);
		execve(command->command, command->params, env_arr);
		ft_error(NOCMMD, command->command);
		return (1);
	}
	close_command_pipes(command);
	return (0);
}
