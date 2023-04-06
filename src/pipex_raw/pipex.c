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

#include "pipex.h"
#include "stdio.h"

static void	set_up_pipes(t_cmd *cmds)
{
	int	i;

	i = 1;
	while (i < cmds->n_cmd)
	{
		if (pipe(cmds->fd[i]) < 0)
			ft_error(EPIPE, "");
		i++;
	}
}

static void	ft_wait(t_cmd *cmds, int *pids)
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

int	main(int ac, char **av, char *envp[])
{
	t_cmd	*cmds;
	pid_t	*pids;
	int		i;

	if (ac < 4)
		ft_error(FEWARG, "");
	pids = NULL;
	cmds = parse_input(ac, av, &pids, envp);
	set_up_pipes(cmds);
	i = 0;
	while (i < cmds->n_cmd)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			ft_error(EPIPE, "");
		if (pids[i] == 0)
			do_child(cmds, i, envp);
		i++;
	}
	close_fds(cmds, cmds->n_cmd);
	ft_wait(cmds, pids);
	free_cmds(&cmds, &pids);
	return (0);
}
