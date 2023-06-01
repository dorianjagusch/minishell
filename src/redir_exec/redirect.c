/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:07:44 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/25 10:07:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"

static void	ft_wait(void)
{
	int	status;

	status = 0;
	if (g_info.exit_value == 0)
	{
		while (wait(&status) > 0)
			;
		if (status > 0 && !g_info.exit_value)
			g_info.exit_value = 130;
		else if (status < 0 && !g_info.exit_value)
			g_info.exit_value = WEXITSTATUS(status);
	}
	return ;
}

static int	**set_up_exe(t_command *command, t_env *env)
{
	int	**pipes;

	g_info.n_cmd = count_commands(command);
	pipes = set_up_pipes(command, g_info.n_cmd);
	if (!pipes)
		return (NULL);
	get_exe_path(&env, command);
	return (pipes);
}

int	redirect_exe(t_command *command, t_env *env)
{
	t_command	*tmp;	
	pid_t		*pids;
	int			**fds;
	int			i;

	if (!command || !env)
		return (-1);
	fds = set_up_exe(command, env);
	pids = ft_calloc(g_info.n_cmd, sizeof(int));
	i = -1;
	tmp = command;
	while (++i < g_info.n_cmd)
	{
		if (exec_builtin(&env, tmp, fds[i + 1][1]) < 0)
		{
			pids[i] = fork();
			if (pids[i] < 0)
				ft_error(EPIPE, "");
			if (pids[i] == 0)
				do_child(command, fds, i, env);
		}
		tmp = tmp->next;
	}
	close_fds(fds, g_info.n_cmd, g_info.n_cmd);
	ft_wait();
	return (0);
}
