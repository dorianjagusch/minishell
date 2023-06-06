/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:13:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/06 13:31:32 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_value(t_env **env)
{
	char	*exit_str;

	exit_str = ft_itoa(g_info.exit_value);
	if (!exit_str)
	{
		ft_error(ENOMEM, "");
		free_env(env);
		exit(1);
	}
	replace_env(env, "?", exit_str);
	g_info.exit_value = 0;
}
