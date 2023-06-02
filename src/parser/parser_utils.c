/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:55:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/02 12:38:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

BOOL	ft_isredir(t_token *token)
{
	if (token->token_type >= greater_than
		&& token->token_type <= less_less)
		return (1);
	return (0);
}
