/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:29:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/08/30 16:49:13 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	const t_builtin	builtins[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"pwd", &ft_pwd},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"env", &ft_env}
	};
	int				i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(cmd->command, builtins[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

BOOL	exec_builtin(t_env **env, t_command *cmd, int out_fd)
{
	const t_builtin	builtins[] = {
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"pwd", &ft_pwd},
	{"export", &ft_export},
	{"unset", &ft_unset},
	{"env", &ft_env}
	};
	int				i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(cmd->command, builtins[i].name) == 0)
			return (builtins[i].builtin(env, cmd, out_fd));
		i++;
	}
	return (-1);
}
