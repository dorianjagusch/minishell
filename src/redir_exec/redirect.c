/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:26:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/02/10 13:34:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_wait(t_command *cmds, int *pids)
{
	int			status;
	int			i;

	status = 0;
	i = 0;
	while (wait(&status) > 0)
		;
	if (status > 0)
	{
		free_cmds(&cmds, &pids);
		ft_error(0, "");
	}
	return ;
}

static int	redirect(t_command *command, t_env *env, size_t n_cmds)
{
	n_cmds = count_commands(command);
	set_up_pipes(command, n_cmds);
	get_fds(command, n_cmds);
	get_exe_path(command, env);
}

int	redirect_exe(t_command *command, t_env *env)
{
	size_t	n_cmds;
	pid_t	*pids;
	char	**env_arr;
	int		*fd[2];
	int		i;

	n_cmds = 0;
	redirect(command, env, n_cmds);
	pids = ft_calloc(n_cmds, sizeof(int));
	env_arr = ft_env_to_array(env);
	i = 0;
	while (i < n_cmds)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(EPIPE, "");
		if (pids[i] == 0)
			do_child(command, i, env);
		i++;
		command = command->next;
	}
	close_fds(cmds, cmds->n_cmd);
	ft_wait(cmds, pids); //to do
	free_cmds(&cmds, &pids);
	return (0);
}
