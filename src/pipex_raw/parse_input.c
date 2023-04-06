/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/02/10 13:28:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_files(t_cmd *cmds, int ac, char **av)
{
	if (access(av[1], F_OK))
		ft_error(NOFILE, av[1]);
	else if (cmds->fd[0][0] < 0 && access(av[1], F_OK) == 0)
		ft_error(NOACCESS, av[1]);
	if (access(av[ac - 1], F_OK))
		ft_error(NOFILE, av[ac - 1]);
	else if (cmds->fd[cmds->n_cmd][1] < 0
		&& access(av[ac - 1], F_OK) == 0)
		ft_error(NOACCESS, av[ac - 1]);
	if (cmds->fd[0][0] < 0 || cmds->fd[cmds->n_cmd][1] < 0)
		ft_error(0, "");
}

static void	get_fds(t_cmd *cmds, int ac, char **av)
{
	int	i;

	i = -1;
	cmds->fd = malloc((cmds->n_cmd + 1) * sizeof(int *));
	if (!cmds->fd)
		ft_error(ENOMEM, "");
	while (++i <= cmds->n_cmd)
	{
		cmds->fd[i] = malloc(sizeof(int) * 2);
		if (!cmds->fd[i])
			ft_error(ENOMEM, "");
	}
	cmds->fd[0][0] = open(av[1], O_RDONLY | O_CLOEXEC);
	cmds->fd[cmds->n_cmd][1] = open(av[ac - 1],
			O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	check_files(cmds, ac, av);
}

t_cmd	*parse_input(int ac, char **av, int **pids, char *envp[])
{
	t_cmd	*cmds;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		ft_error(ENOMEM, "");
	cmds->n_cmd = ac - 3;
	get_fds(cmds, ac, av);
	parse_cmds(cmds, ac, av, envp);
	*pids = malloc(sizeof(int) * cmds->n_cmd);
	if (!*pids)
		ft_error(ENOMEM, "");
	return (cmds);
}
