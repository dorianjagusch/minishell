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

void	ft_wait(void)
{
	int				status;

	status = 0;
	if (g_info.exit_value == 0)
	{
		while (wait(&status) > 0)
			;
		if (status > 0 && !g_info.exit_value)
			g_info.exit_value = NOCMMD;
		else if (status < 0 && !g_info.exit_value)
			g_info.exit_value = WEXITSTATUS(status);
		if (WIFSIGNALED(status) == 1)
		{
			g_info.exit_value = 130;
			if (WTERMSIG(status) == 3)
			{
				write(1, "Quit: 3", 8);
				g_info.exit_value = 131;
			}
			write(1, "\n", 1);
		}
		global_signal(ON);
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
	int			i;

	if (!command || !env)
		return (-1);
	g_info.fds = set_up_exe(command, env);
	g_info.pids = ft_calloc(g_info.n_cmd, sizeof(int));
	i = -1;
	tmp = command;
	global_signal(OFF);
	while (++i < g_info.n_cmd)
	{
		if (command->success >= 0
			&& exec_builtin(&env, tmp, g_info.fds[i + 1][1]) < 0)
		{
			g_info.pids[i] = fork();
			if (g_info.pids[i] < 0)
				ft_error(EPIPE, "");
			if (g_info.pids[i] == 0)
				exe_child(command, g_info.fds, i, env);
		}
		tmp = tmp->next;
	}
	close_fds(g_info.fds, g_info.n_cmd, g_info.n_cmd);
	return (0);
}
