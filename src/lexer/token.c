/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/03 16:04:06 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	re_label(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;

	if (temp->token_type == GREATER_THAN || temp->token_type == LESS_THAN
		|| temp->token_type == LESS_LESS
		|| temp->token_type == GREATER_GREATER)
		temp->next->next->token_type = COMMAND;
	else
		temp->token_type = COMMAND;
	while (temp != NULL)
	{
		if (temp->token_type == PIPE)
		{
			temp = temp->next;
			if (temp->token_type == LESS_LESS || temp->token_type == LESS_THAN
				|| temp->token_type == GREATER_THAN
				|| temp->token_type == GREATER_GREATER)
			temp->next->next->token_type = COMMAND;
			else
				temp->token_type = COMMAND;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
