/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:56:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/07 09:08:50 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*skip_to_pipe(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->token_type != pipe_sym)
		tmp = tmp->next;
	return (tmp);
}

static t_token	*redir_command(t_token *token, t_command *command)
{
	if (token->token_type >= less_than)
	{
		if (command->infile)
			ft_free(command->infile);
		command->infile = ft_strdup(token->next->content);
		if (!command->infile)
			ft_error(ENOMEM, "");
		command->in_redirect = token->token_type;
	}
	else
	{
		if (command->outfile)
			free(command->outfile);
		command->outfile = ft_strdup(token->next->content);
		if (!command->outfile)
			ft_error(ENOMEM, "");
		command->out_redirect = token->token_type;
	}
	get_fds(command, token);
	return (token->next);
}

int	extract_command(t_token *token, t_command *command, int id)
{
	t_token		*tmp;
	int			params_flag;

	tmp = token;
	params_flag = 0;
	while (tmp)
	{
		if (handle_strings(command, tmp, &params_flag, id) < 0)
			return (-1);
		if (tmp->token_type == pipe_sym)
		{
			command->next = init_command(tmp->next, id);
			return (0);
		}
		else if (tmp->token_type != string && tmp->token_type != command_type)
			tmp = redir_command(tmp, command);
		if (command->success < 0)
			tmp = skip_to_pipe(token);
		else if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

t_command	*init_command(t_token *token, int id)
{
	t_command	*command;

	if (!token)
		return (NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	if (extract_command(token, command, id) < 0)
	{
		free_command(&command);
		return (NULL);
	}
	return (command);
}
