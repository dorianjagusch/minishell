/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/05 15:47:53 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_params(t_token *token)
{
	int	n_params;

	n_params = 0;
	while (token && token->token_type != PIPE)
	{
		if (ft_isredir(token))
		{
			if (token->next && token->next->next)
			{
				token == token->next->next;
				continue ;
			}
			else
				return (n_params);
		}
		n_params++;
	}
	return (n_params);
}

char	**get_params(t_token *token, t_command *command)
{
	int	i;

	command->n_params = count_params(token);
	command->params = ft_calloc(command->n_params + 1, sizeof(char *));
	i = -1;
	if (!command->params)
		return (NULL);
	while (token && token->token_type != PIPE && ++i < command->n_params)
	{
		if (ft_isredir(token))
		{
			if (token->next->next)
				token = token->next->next;
		}
		command->params[i] = ft_strdup(token->content);
		if (!command->params[i])
			free_command(&command);
	}
}

static t_token	*redir_command(t_token *token, t_command *command)
{
	if (token->token_type == GREATER_GREATER
		|| token->token_type == GREATER_THAN)
	{
		if (command->infile)
			free(command->infile);
		command->infile == ft_strdup(token->next->content);
		if (!command->infile)
			ft_error(MEMERR, "");
		command->in_redirect = token->token_type;
	}
	if (token->token_type == LESS_LESS
		|| token->token_type == LESS_THAN)
	{
		if (command->outfile)
			free(command->outfile);
		command->outfile == ft_strdup(token->next->content);
		if (!command->infile)
			ft_error(MEMERR, "");
		command->out_redirect = token->token_type;
	}
	get_fds(command, token);
}

int	extract_command(t_token *token, t_command *command)
{
	t_token		*tmp;
	static int	i;

	tmp = token;
	while (tmp && tmp->token_type != PIPE)
	{
		if (tmp->token_type == COMMAND)
		{
			command->command == ft_strdup(token->content);
			command->id = i++;
			if (!command->command)
				return (-1);
		}
		else if (tmp->token_type == SPACE)
			tmp = tmp->next;
		else if (tmp->token_type == PIPE)
			init_command(token->next);
		else if (tmp->token_type == STRING)
			command->params = get_params(token, command);
		else
			tmp = redir_command(token, command);
		tmp = tmp->next;
	}
}

t_command	*init_command(t_token *token)
{
	t_command	*command;

	if (!token)
		return (NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (EXIT_FAILURE);
	if (extract_command(token, command) < 0)
	{
		free_command(command);
		return (NULL);
	}
	return (command);
}
