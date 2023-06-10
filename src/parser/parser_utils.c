/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:55:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/10 10:00:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "libft.h"
#include "ft_error.h"
#include <errno.h>

BOOL	ft_isredir(t_token *token)
{
	if (token->token_type >= greater_than
		&& token->token_type <= less_less)
		return (1);
	return (0);
}

static int	count_params(t_token *token)
{
	int	n_params;

	n_params = 0;
	while (token && token->token_type != pipe_sym)
	{
		if (ft_isredir(token))
		{
			if (token->next->next)
			{
				token = token->next->next;
				continue ;
			}
			else
				return (n_params);
		}
		if (token->token_type == string || token->token_type == command_type)
			n_params++;
		token = token->next;
	}
	return (n_params);
}

static void	get_params(t_token *token, t_command *command)
{
	int	i;

	command->n_params = count_params(token);
	command->params = ft_calloc(command->n_params + 1, sizeof(char *));
	i = 0;
	if (!command->params)
	{
		free_command(&command);
		ft_error(ENOMEM, "");
	}
	while (token && token->token_type != pipe_sym && i < command->n_params)
	{
		if (ft_isredir(token))
				token = token->next->next;
		command->params[i] = ft_strdup(token->content);
		if (!command->params[i++])
			free_command(&command);
		token = token->next;
	}
}

void	handle_strings(t_command *command, t_token *token, int *params_flag,
	int id)
{
	if ((token->token_type == string || token->token_type == command_type)
		&& !*params_flag)
	{
		get_params(token, command);
		*params_flag = 1;
	}
	if (token->token_type == command_type)
	{
		command->command = ft_strdup(token->content);
		command->id = id++;
		if (!command->command)
			ft_error(ENOMEM, "");
		if (chdir(command->command) == 0)
			command->success = 2;
	}
}
