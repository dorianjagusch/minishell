/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/26 13:27:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char *path, t_ev **env)
{
	t_ev	*oldpwd;
	t_ev	*pwd;

	if (!path)
		return (EXIT_FAILURE);
	if (chdir(path))
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
	pwd->value = ft_strdup(path);
	return (EXIT_SUCCESS);
}
