/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:13:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/05 17:25:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_value(t_env **env)
{
	char	*exit_str;

	exit_str = ft_itoa(g_info.exit_value);
	ft_printf("%p\n", exit_str);
	if (!exit_str)
	{
		ft_error(ENOMEM, "");
		free_env(env);
		exit(1);
	}
	ft_printf("%p\n", exit_str);
	replace_env(env, "?", exit_str);
	ft_printf("%p\n", exit_str);
	free(exit_str);
	ft_printf("penis\n");
	g_info.exit_value = 0;
}
