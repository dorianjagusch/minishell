/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/29 13:20:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int	get_params(t_token *tokens, t_command *command)
{
	size_t	i;

	i = 0;
	while (tokens->token_type == STRING)
	{
		command->params[i++] = ft_strdup(tokens->content);
		tokens = tokens->next;
	}
	return ((int) i);
}

t_command	*get_file_info(t_token *tokens, t_command *command)
{
	if (tokens->token_type == GREATER_THAN
		|| tokens->token_type == GREATER_GREATER)
	{
		command->outfile = ft_strdup(tokens->next->content);
		command->out_redirect = ft_strdup(tokens->content);
	}
	else if (tokens->token_type == LESS_THAN || tokens->token_type == LESS_LESS)
	{
		command->infile = ft_strdup(tokens->next->content);
		command->in_redirect = ft_strdup(tokens->content);
	}
	return (tokens->next);
}

t_command	*new_command(t_token *tokens)
{
	t_command	*command;
	t_token		*tmp;

	if (!tokens)
		return (NULL);
	tmp = tokens;
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	while (tmp)
	{
		if (tmp->token_type == COMMAND)
			command->command = ft_strdup(tmp->content);
		else if (tmp->token_type == STRING)
			command->n_params = get_params(tmp, command);
		else if (tmp->token_type == PIPE)
		{
			command->next = new_command(tmp->next);
			return (command);
		}
		else
			tmp = get_file_info(tmp, command);
		tmp = tmp->next;
	}
}
