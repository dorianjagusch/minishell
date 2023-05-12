/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:02:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/10 16:05:02 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	const char	*quotes[] = {
		">",
		">>",
		"<",
		"<<"
	};

	while (token)
	{
		if (token->token_type == STRING)
			ft_printf("string: %s\n", token->content);
		else if (token->token_type == COMMAND)
			ft_printf("cmd: %s\n", token->content);
		else if (token->token_type >= GREATER_THAN
			&& token->token_type <= LESS_LESS)
			ft_printf("%s\n", quotes[token->token_type - GREATER_THAN]);
		else if (token->token_type == PIPE)
			ft_printf("%s\n", token->content);
		else if (token->token_type == SPACE)
			ft_printf("SPACE: %s\n", token->content);
		printf("quote: %d\n", token->isquote);
		printf("=====================\n");
		token = token->next;
	}
}