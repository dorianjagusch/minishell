/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/10 15:47:23 by djagusch         ###   ########.fr       */
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
			if (token->next->next)
			{
				token = token->next->next;
				continue ;
			}
			else
				return (n_params);
		}
		if (token->token_type == STRING || token->token_type == COMMAND)
			n_params++;
		token = token->next;
	}
	return (n_params);
}

void	get_params(t_token *token, t_command *command)
{
	int	i;

	command->n_params = count_params(token);
	command->params = ft_calloc(command->n_params + 1, sizeof(char *));
	i = 0;
	if (!command->params)
	{
		free_command(&command);
		ft_error(MEMERR, "");
	}
	while (token && token->token_type != PIPE && i < command->n_params)
	{
		if (ft_isredir(token))
				token = token->next->next;
		command->params[i] = ft_strdup(token->content);
		if (!command->params[i++])
			free_command(&command);
		token = token->next;
	}
}

static t_token	*redir_command(t_token *token, t_command *command)
{
	if (token->token_type >= LESS_THAN)
	{
		if (command->infile)
			free(command->infile);
		command->infile = ft_strdup(token->next->content);
		if (!command->infile)
			ft_error(MEMERR, "");
		command->in_redirect = token->token_type;
	}
	else
	{
		if (command->outfile)
			free(command->outfile);
		command->outfile = ft_strdup(token->next->content);
		if (!command->outfile)
			ft_error(MEMERR, "");
		command->out_redirect = token->token_type;
	}
	get_fds(command, token);
	return (token->next);
}

int	extract_command(t_token *token, t_command *command)
{
	t_token		*tmp;
	static int	i;
	int			params_flag;

	tmp = token;
	params_flag = 0;
	while (tmp)
	{
		if (tmp->token_type == COMMAND)
		{
			command->command = ft_strdup(token->content);
			command->id = i++;
			if (!command->command)
				return (-1);
		}
		else if (tmp->token_type == PIPE)
			command->next = init_command(token->next);
		else if (tmp->token_type == STRING && !params_flag)
		{
			get_params(token, command);
			params_flag = 1;
		}
		else if (tmp->token_type != STRING && tmp->token_type != COMMAND)
			tmp = redir_command(tmp, command);
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

t_command	*init_command(t_token *token)
{
	t_command	*command;

	if (!token)
		return (NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	if (extract_command(token, command) < 0)
	{
		free_command(&command);
		return (NULL);
	}
	return (command);
}
