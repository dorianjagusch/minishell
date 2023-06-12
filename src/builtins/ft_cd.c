/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/12 11:24:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_command *cmd, int home_exists)
{
	char	*error_msg;

	if (!home_exists)
	{
		ft_error(DEFERR, "cd: HOME not set");
		return ;
	}
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
		if (pwd->value)
			oldpwd->value = pwd->value;
		else
			oldpwd->value = ft_strdup("");
	}
	else
	{
		add_env(env, new_env("OLDPWD", pwd->value));
		free(pwd->value);
	}
	if (pwd)
		pwd->value = ft_strdup(getcwd(cur_dir, PATH_MAX));
}

static int	change_to_home(t_env **env, t_command *cmd)
{
	char	*home;

	home = find_value(env, "HOME");
	if (!home)
	{
		cd_error(cmd, 0);
		return (1);
	}
	chdir(home);
	return (0);
}

int	ft_cd(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*oldpwd;
	t_env	*pwd;
	char	cur_dir[PATH_MAX];

	(void) out_fd;
	if (cmd->n_params == 1)
		return (change_to_home(env, cmd));
	getcwd(cur_dir, PATH_MAX);
	if (chdir(cmd->params[1]))
	{
		cd_error(cmd, 1);
		return (EXIT_FAILURE);
	}
	oldpwd = find_env(env, "OLDPWD", 0);
	pwd = find_env(env, "PWD", 0);
	manage_wd_vars(env, pwd, oldpwd, cur_dir);
	return (EXIT_SUCCESS);
}
