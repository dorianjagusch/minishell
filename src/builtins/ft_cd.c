/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/08 13:22:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(t_command *cmd)
{
	char	*error_msg;

	error_msg = ft_strjoin("cd: ", cmd->params[1]);
	if (!error_msg)
	{
		ft_error(ENOMEM, "");
		ft_clear_everything(&g_info);
		exit(ENOMEM);
	}
	ft_error(ENOENT, error_msg);
	free(error_msg);
}

void	manage_wd_vars(t_env **env, t_env *pwd, t_env *oldpwd, char *cur_dir)
{
	if (oldpwd)
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(cur_dir);
	}
	else
		add_env(env, new_env("OLDPWD", cur_dir));
	if (pwd)
	{
		if (pwd->value)
			free(pwd->value);
		pwd->value = ft_strdup(getcwd(cur_dir, PATH_MAX));
	}
}


int	ft_cd(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	cur_dir[PATH_MAX];

	if (!cmd->params[1] || out_fd < 0)
		return (EXIT_FAILURE);
	getcwd(cur_dir, PATH_MAX);
	if (chdir(cmd->params[1]))
	{
		cd_error(cmd);
		return (EXIT_FAILURE);
	}
	oldpwd = find_env(env, "OLDPWD", 0);
	pwd = find_env(env, "PWD", 0);
	manage_wd_vars(env, pwd, oldpwd, cur_dir);
	return (EXIT_SUCCESS);
}
