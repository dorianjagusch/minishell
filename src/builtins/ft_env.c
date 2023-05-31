/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/31 14:40:46 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env **env, t_command *cmd, int out_fd)
{
	t_env	*tmp;

	tmp = *env;
	cmd = NULL;
	while (tmp)
	{
		ft_printf_fd(out_fd, "%s=%s\n", tmp->key, tmp->value);
		if (tmp->next && ft_strcmp(tmp->next->value, "?") == 0)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

