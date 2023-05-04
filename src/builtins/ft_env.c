/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 16:00:52 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **env, t_command *cmd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_printf_fd(cmd->out_fd[1], "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

