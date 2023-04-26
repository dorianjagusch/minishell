/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:22 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/26 17:40:04 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_ev **env, char *variable)
{
	t_ev	*remove;

	if (!env || !*env)
		return (EXIT_FAILURE);
	remove = find_env(env, variable);
	if (remove)
	{
		ft_free(remove->value);
		remove->value = ft_calloc(1, sizeof(char));
	}
	return (0);
}
