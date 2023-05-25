/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 13:29:10 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/25 10:07:05 by djagusch         ###   ########.fr       */
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

BOOL	exec_builtin(t_env **env, t_command *cmd)
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
	while (i < 7)
	{
		if (ft_strcmp(cmd->command, builtins[i].name) == 0)
			return (builtins[i].builtin(env, cmd));
	}
	return (-1);
}
