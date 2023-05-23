/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:52:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/09 11:52:55 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirect.h"
#include <stdio.h>

static void	set_pipes(t_command *command, int *pipes)
{
	if (pipe(pipes) < 0)
		ft_error(EPIPE, "");
	if (command->infile)
	{
		if (close(pipes[0]) < 0)
			ft_error(EPIPE, "");
		pipes[0] = dup(command->fds[0]);
	}
	if (command->outfile)
	{
		if (close(pipes[1]) < 0)
			ft_error(EPIPE, "");
		if (command->fds[1])
			pipes[1] = dup(command->fds[1]);
		else
			pipes[1] = dup(STDIN_FILENO);
	}
}

static int	*set_up_pipes(t_command *command, int n_cmd)
{
	int	i;
	int	*pipes;

	i = 2;
	pipes = malloc(2 * (n_cmd + 1));
	pipes[0] = command->fds[0];
	if (command)
	{
		while (i < 2 * n_cmd)
		{
			set_pipes(command, pipes + i);
			i += 2;
			command = command->next;
		}
	}
	pipes[i + 1] = command->fds[1];
	return (pipes);
}

static void	ft_wait(void)
{
	int			status;

	status = 0;
	while (wait(&status) > 0)
		;
	if (status > 0)
		ft_error(0, "");
	return ;
}

static int	*set_up_exe(t_command *command, t_env *env, int *n_cmds)
{
	int	*pipes;

	*n_cmds = count_commands(command);
	pipes = set_up_pipes(command, *n_cmds);
	get_exe_path(&env, command);
	return (pipes);
}

int	redirect_exe(t_command *command, t_env *env)
{
	int			n_cmds;
	t_command	*tmp;	
	pid_t		*pids;
	int			*fds;
	int			i;

	n_cmds = 0;
	if (!command || !env)
		return (-1);
	fds = set_up_exe(command, env, &n_cmds);
	pids = ft_calloc(n_cmds, sizeof(int));
	i = 0;
	tmp = command;
	printf("Here\n");
	while (i < n_cmds)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(EPIPE, "");
		if (pids[i++] == 0)
			do_child(tmp, fds, n_cmds, env);
		tmp = tmp->next;
	}
	close_command_pipes(command);
	close_fds(fds, n_cmds, n_cmds);
	ft_wait();
	ft_clear(&command, &pids, &fds);
	return (0);
}
