/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/27 13:16:17 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

t_command	*new_command(t_token *token)
{
	t_command	*command;
	int			i;

	if (!token)
		return (NULL);
	i = 0;
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	if (token->token_type == COMMAND)
		command->command = ft_strdup(token->content);
	else if (token->token_type == STRING)
		command->params[i] = ft_strdup(token->content);

}
