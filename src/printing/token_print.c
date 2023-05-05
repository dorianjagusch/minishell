/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:02:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 17:13:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	while (token)
	{
		if (token->token_type == STRING)
			ft_printf("string: %s\n", token->content);
		else if (token->token_type == COMMAND)
			ft_printf("cmd: %s\n", token->content);
		else if (token->token_type == GREATER_GREATER)
			ft_printf(">>: %d\n", token->content);
		else if (token->token_type == GREATER_THAN)
			ft_printf("> %d\n", token->content);
		else if (token->token_type == LESS_LESS)
			ft_printf("param: %d\n", token->content);
		else if (token->token_type == LESS_THAN)
			ft_printf("param: %d\n", token->content);
		else if (token->token_type == PIPE)
			ft_printf("%s\n", token->content);
		else if (token->token_type == SPACE)
			ft_printf("SPACE: %s\n", token->content);
		printf("quote: %d\n", token->isquote);
		token = token->next;
	}
}