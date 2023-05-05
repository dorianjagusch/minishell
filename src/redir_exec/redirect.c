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

static void	set_up_pipes(t_command *command, int *pipes)
{
	int	i;

	i = 1;
	while (i < pipes)
	{
		if (pipe(pipes) < 0)
			ft_error(EPIPE, "");
		i++;
	}
}

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

static char	**set_up_exe(t_command *command, t_env *env, size_t *n_cmds)
{
	char	**env_arr;

	*n_cmds = count_commands(command);
	set_up_pipes(command, *n_cmds);
	get_exe_path(command, env);
	env_arr = ft_env_to_array(env);
}

//set_up_pipes is not taking the array yet. Need to work out how to let the already open files go in there.
// Also need to remember to close the files that were opened and then closed in parser.c

int	redirect_exe(t_command *command, t_env *env)
{
	size_t	n_cmds;
	pid_t	*pids;
	char	**env_arr;
	int		*fds[2];
	int		i;

	n_cmds = 0;
	env_arr = set_up_exe(command, env, *n_cmds);
	pids = ft_calloc(n_cmds, sizeof(int));
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
	close_fds(command, n_cmds);
	ft_wait(command, pids); //to do
	free_cmds(&command, &pids);
	return (0);
}
