/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:10:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 18:12:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_commands(t_command *commands)
{
	t_command	*tmp;
	size_t		count;

	tmp = commands;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
}
