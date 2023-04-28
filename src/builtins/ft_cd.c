/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/27 11:37:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_ev **env, t_command *cmd)
{
	t_ev	*oldpwd;
	t_ev	*pwd;

	if (!cmd->params[1])
		return (EXIT_FAILURE);
	if (chdir(cmd->params[1]))
	{
		perror("MiniShell$: cd:");
		return (errno);
	}
	oldpwd = find_env(env, "OLDPWD");
	pwd = find_env(env, "PWD");
	if (!oldpwd)
		add_env(&env, new_env("OLDPWD", pwd->value));
	else
		oldpwd->value = pwd->value;
	pwd->value = ft_strdup(cmd->params[1]);
	return (EXIT_SUCCESS);
}
