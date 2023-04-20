/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:13 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/15 15:31:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_ev *env)
{
	t_ev	*tmp;

	ft_error("env", EPATH);
	tmp = env;
	while (tmp->next)
	{
		ft_putstr(tmp->key);
		ft_putstr(tmp->value);
		tmp = tmp->next;
	}
}