/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/14 09:41:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_cmd *cmds, int cur)
{
	size_t	pipe;

	pipe = 0;
	while (pipe <= cmds->n_cmd)
	{
		if (pipe != cur && pipe != cmds->n_cmd)
			close(cmds->fd[pipe][0]);
		if (pipe != cur + 1 && pipe != 0)
			close(cmds->fd[pipe][1]);
		pipe++;
	}
}

void	free_cmds(t_cmd **cmds, int **pids)
{
	int	i;

	i = 0;
	while (i < (*cmds)->n_cmd)
	{
		if (!(*cmds)->params[i] || !(*cmds)->n_params[i])
		{
			ft_free_array(&((*cmds)->params[i]), (*cmds)->n_params[i]);
			if (!(*cmds)->cmd)
				ft_free((*cmds)->cmd[i]);
		}
		ft_free((*cmds)->fd[i]);
		i++;
	}
	ft_free((*cmds)->fd[(*cmds)->n_cmd]);
	ft_free((*cmds)->fd);
	ft_free((*cmds)->cmd);
	ft_free((*cmds)->params);
	ft_free((*cmds)->n_params);
	ft_free(*cmds);
	ft_free(*pids);
}

size_t	count_elements(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	ft_error(int error, char *str)
{	
	if (error == 0)
		exit(1);
	if (error == NOFILE)
		ft_printf_fd("pipex: no such file or directory: %s\n",
			STDERR_FILENO, str);
	else if (error == NOACCESS)
		ft_printf_fd("pipex: %s: %s\n", STDERR_FILENO, strerror(EACCES), str);
	else
	{
		if (error == EACCES)
			ft_printf_fd("pipex: %s: %s\n", STDERR_FILENO,
				strerror(error), str);
		else if (error == NOCMMD)
			ft_printf_fd("pipex: command not found: %s\n", STDERR_FILENO, str);
		else if (error == FEWARG)
			ft_printf_fd("pipex: too few arguments\n", STDERR_FILENO);
		else if (error == BIGARG)
			ft_printf_fd("pipex: too many arguments\n", STDERR_FILENO);
		exit(error);
	}
}
