/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:55:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/10 10:49:19 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"


BOOL	ft_isredir(t_token *token)
{
	if (token->token_type >= GREATER_THAN
		|| token->token_type <= LESS_LESS)
		return (1);
	return (0);
}

t_command	*set_command(t_command *head, size_t id)
{
	t_command	*tmp;

	tmp = head;
	if (tmp)
	{
		while (tmp->id != id)
			tmp = tmp->next;
	}
	return (tmp);
}
