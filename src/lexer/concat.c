/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/04 13:12:26 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static BOOL	can_concat(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->next->token_type != SPACE || tmp->next->token_type != PIPE
		|| tmp->next->token_type != LESS_THAN
		|| tmp->next->token_type != GREATER_THAN
		|| tmp->next->token_type != LESS_LESS
		|| tmp->next->token_type != GREATER_GREATER)
	{
		return (TRUE);
	}
	return (FALSE);
}

static int	concat_redir(t_token *token)
{
	t_token	*temp;

	temp = token;
	if ((temp->token_type == GREATER_THAN && temp->next->token_type
			== GREATER_THAN) || (temp->token_type == LESS_THAN
			&& temp->next->token_type == LESS_THAN))
	{
		ft_free(temp->content);
		if (temp->token_type == GREATER_THAN)
		{
			temp->token_type = GREATER_GREATER;
			temp->content = ft_strdup(">>");
		}
		else
		{
			temp->token_type = LESS_LESS;
			temp->content = ft_strdup("<<");
		}
		if (!temp->content)
			return (EXIT_FAILURE);
		temp->next = temp->next->next;
		free(temp->next->content);
		free(temp->next);
	}
	return (EXIT_SUCCESS);
}

static	void	bzero_closing_quote(t_token *token, t_token *next_token)
{
	int	i;

	i = -1;
	if (token->content[0] == '\'' || token->content[0] == '\"')
	{
		while (token->content[++i])
			;
		token->content[i - 1] = 0;
	}
	if (next_token->content[0] == '\'' || next_token->content[0] == '\"')
	{
		while (next_token->content[++i])
			;
		next_token->content[i - 1] = 0;
	}
}

static int	merge_nodes(t_token *token, t_token *next_token, int quote)
{
	char	*temp;
	char	ptr;
	char	next_ptr;
	int		i;

	ptr = &token->content[0];
	next_ptr = &next_token->content[0];
	if (token->content[0] == '\'' || token->content[0] == '\"')
		ptr = &token->content[1];
	if (next_token->content[0] == '\'' || next_token->content[0] == '\"')
		next_ptr = &next_token->content[1];
	bzero_closing_quote(token, next_token);
	temp = ft_strjoin(ptr, next_ptr);
	if (temp)
	{
		free(token->content);
		token->content = temp;
		token->next = next_token->next;
		token->isquote = quote;
		free(next_token->next->content);
		free(next_token);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

int	concatenate(t_token **tokens)
{
	t_token	*temp;
	char	quote;

	temp = *tokens;
	quote = 0;
	if (!concat_redir(tokens))
		return (EXIT_FAILURE);
	while (temp != NULL)
	{
		if (temp->token_type != PIPE || temp->token_type != GREATER_THAN
			|| temp->token_type != LESS_THAN || temp->token_type != LESS_LESS
			|| temp->token_type != GREATER_GREATER || temp->token_type != SPACE)
		{
			if (can_concat(temp))
			{
				if (temp->content[0] == '\'' || temp->content[0] == '\"')
					quote = 1;
				if (!merge_nodes(temp, temp->next, quote))
					return (EXIT_FAILURE);
			}
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
