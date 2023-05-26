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
#include <stdio.h>

static void	ft_wait(void)
{
	int			status;

	status = 0;
	while (wait(&status) > 0)
		;
	if (status > 0)
		ft_error(0, "STATUS ERROR");
	return ;
}

static int	**set_up_exe(t_command *command, t_env *env, int *n_cmds)
{
	int	**pipes;

	*n_cmds = count_commands(command);
	pipes = set_up_pipes(command, *n_cmds);
	if (!pipes)
		return (NULL);
	get_exe_path(&env, command);
	return (pipes);
}

int	redirect_exe(t_command *command, t_env *env)
{
	int			n_cmd;
	t_command	*tmp;	
	pid_t		*pids;
	int			**fds;
	int			i;

	n_cmd = 0;
	if (!command || !env)
		return (-1);
	fds = set_up_exe(command, env, &n_cmd);
	ft_print_fds(fds, n_cmd + 1);
	pids = ft_calloc(n_cmd, sizeof(int));
	i = -1;
	tmp = command;
	while (++i < n_cmd)
	{
		if (exec_builtin(&env, tmp, fds[i + 1][1]) < 0)
		{
			pids[i] = fork();
			if (pids[i] < 0)
				ft_error(EPIPE, "fail");
			if (pids[i] == 0)
				do_child(command, fds, i, env);
		}
		printf("command: %s\n", tmp->command);
		tmp = tmp->next;
	}
	printf("parent closes fds\n");
	close_fds(fds, n_cmd, n_cmd);
	printf("parent has closed fds\n");
	ft_wait();
	//ft_clear(&command, &pids, &fds, n_cmd + 1);
	return (0);
}

void	ft_print_fds(int **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("reading fd: %d\n", arr[i][0]);
		printf("writing fd: %d\n", arr[i][1]);
		printf("=====================\n");
		i++;
	}

}