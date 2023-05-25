/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/22 14:12:27 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_env **env, t_command *cmd)
{
	t_env	*oldpwd;
	t_env	*pwd;

	if (!cmd->params[1])
		return (EXIT_FAILURE);
	if (chdir(cmd->params[1]))
	{
		perror("MiniShell$: cd:");
		return (errno);
	}
	oldpwd = find_env(env, "OLDPWD", 0);
	pwd = find_env(env, "PWD", 0);
	if (!oldpwd)
		add_env(env, new_env("OLDPWD", pwd->value));
	else
		oldpwd->value = pwd->value;
	pwd->value = ft_strdup(cmd->params[1]);
	return (EXIT_SUCCESS);
}
