/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:22:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/17 16:03:10 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "parser.h"
#include "minishell.h"


void	do_child(t_command *command, int *fds, int n_cmd, t_env *env)
{
	int			current;
	char		**env_arr;

	current = command->id;
	ft_printf("%d\n", current);
	close_fds(fds, current, n_cmd);
	if (dup2(fds[current], STDIN_FILENO) < 0
		|| dup2(fds[current + 1], STDOUT_FILENO) < 0)
		ft_error(0, "");
	close(fds[current]);
	close(fds[current + 1]);
	if (!command->command)
		ft_error(NOCMMD, "");
	if (exec_builtin(&env, command))
	{
		env_arr = ft_env_to_array(env);
		execve(command->command, command->params, env_arr);
		ft_error(NOCMMD, command->command);
	}
}
