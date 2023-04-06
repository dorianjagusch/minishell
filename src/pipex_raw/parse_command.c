/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:57:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/02/12 15:57:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_paths(char ***paths, char *raw_path)
{
	size_t	len;

	if (paths)
	{
		len = count_elements(*paths);
		ft_free_array(paths, len);
	}
	if (raw_path)
		ft_free(raw_path);
}

static char	*find_path(char **path, char **cmd_name)
{
	size_t	i;
	size_t	len;
	char	**paths;
	char	*raw_path;
	char	*test_path;

	i = 0;
	paths = ft_split(*path, ':');
	len = count_elements(paths);
	while (i < len)
	{
		raw_path = ft_strjoin(paths[i], "/");
		test_path = ft_strjoin(raw_path, *cmd_name);
		if (access(test_path, X_OK) == 0)
		{
			ft_free_paths(&paths, raw_path);
			return (test_path);
		}
		ft_free(raw_path);
		ft_free(test_path);
		i++;
	}
	ft_free_paths(&paths, NULL);
	return (ft_strdup(*cmd_name));
}

static char	*get_exe_path(char	*cmd_name, char *envp[])
{
	char	*path;
	char	*exe_path;
	size_t	i;

	i = -1;
	while (envp[++i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path += 5;
			exe_path = find_path(&path, &cmd_name);
			if (exe_path)
				return (exe_path);
		}
	}
	return (NULL);
}

static void	ft_malloc_cmd(t_cmd *cmds)
{
	cmds->cmd = malloc(sizeof(char *) * (cmds->n_cmd));
	if (!cmds->cmd)
	{
		ft_error(ENOMEM, "");
	}
	cmds->params = malloc(sizeof(char **) * (cmds->n_cmd));
	if (!cmds->params)
	{
		ft_free(cmds->cmd);
		ft_error(ENOMEM, "");
	}
	cmds->n_params = malloc(sizeof(int) * cmds->n_cmd);
	if (!cmds->n_params)
	{
		ft_free(cmds->cmd);
		ft_free(cmds->params);
		ft_error(ENOMEM, "");
	}
}

void	parse_cmds(t_cmd *cmds, int ac, char **av, char *envp[])
{
	size_t	i;

	i = 0;
	ft_malloc_cmd(cmds);
	while (i < cmds->n_cmd)
	{
		cmds->params[i] = ft_split2(av[i + 2]);
		if (cmds->params[i] && cmds->params[i][0])
		{
			cmds->n_params[i] = count_elements(cmds->params[i]);
			cmds->cmd[i] = get_exe_path(cmds->params[i][0], envp);
		}
		else
			cmds->cmd[i] = NULL;
		i++;
	}
}
