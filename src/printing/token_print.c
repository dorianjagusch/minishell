/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:02:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 16:57:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	t_token	tmp;

	while (token)
	{
		if (token->token_type == STRING)
			ft_printf("string: %s\n", token->content);
		if (token->token_type == COMMAND)
			ft_printf("cmd: %s\n", token->content);
		if (token->token_type == GREATER_GREATER)
			ft_printf(">>: %d\n", token->content);
		if (token->token_type == GREATER_THAN)
			ft_printf("> %d\n", token->content);
		if (token->token_type == LESS_LESS)
			ft_printf("param: %d\n", token->content);
		if (token->token_type == LESS_THAN)
			ft_printf("param: %d\n", token->content);
		if (token->token_type == PIPE)
			ft_printf("%s\n", token->content);
		if (token->token_type == PIPE)
			ft_printf("SPACE: %s\n", token->content);
	}
}