/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/11 14:58:19 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	concat_redir(t_token **token)
{
	ft_printf("in concat redir\n");
	if (((*token)->token_type == GREATER_THAN && (*token)->next->token_type
			== GREATER_THAN) || ((*token)->token_type == LESS_THAN
			&& (*token)->next->token_type == LESS_THAN))
	{
		ft_free((*token)->content);
		if ((*token)->token_type == GREATER_THAN)
		{
			(*token)->token_type = GREATER_GREATER;
			(*token)->content = ft_strdup(">>");
		}
		else
		{
			(*token)->token_type = LESS_LESS;
			(*token)->content = ft_strdup("<<");
		}
		if (!(*token)->content)
			return (EXIT_FAILURE);
		(*token)->next = (*token)->next->next;
		free((*token)->next->content);
		free((*token)->next);
	}
	ft_printf("exiting concat redir with success\n");
	return (EXIT_SUCCESS);
}

static	int	bzero_quote(t_token *token, t_token *next_token)
{
	char	*temp;

	if ((token->content)[0] == '\'' || (token->content)[0] == '\"')
	{
		temp = ft_substr(token->content , 1 , ft_strlen(token->content) - 2);
		if (temp)
		{
			free(token->content);
			token->content = temp;
		}
		else
			return (EXIT_FAILURE);
		
	}
	if ((next_token->content)[0] == '\'' || (next_token->content)[0] == '\"')
	{
		temp = ft_substr(next_token->content , 1 , ft_strlen(next_token->content) - 2);
		if (temp)
		{
			free(next_token->content);
			next_token->content = temp;
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	merge_nodes(t_token **token, t_token **next_token, int quote)
{
	char	*temp;

	ft_printf("in merge nodes\n");
	if (((*token)->content)[0] == '\'' || ((*token)->content)[0] == '\"' 
		|| (*next_token)->content[0] == '\'' || (*next_token)->content[0] == '\"')
		if (bzero_quote((*token), (*next_token)) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	temp = ft_strjoin((*token)->content, (*next_token)->content);
	if (temp)
	{
		ft_printf("temp : %s\n", temp);
		free((*token)->content);
		(*token)->content = temp;
		ft_printf("content : %s\n", (*token)->content);
		(*token)->next = (*next_token)->next;
		(*token)->isquote = quote;
		free((*next_token)->content);
//		free((*next_token));
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}

static int	quote_exist(t_token *token)
{
	if ((token->content)[0] == '\'' || (token->content)[0] == '\"'
			|| token->isquote == 1 || (token->next->content)[0] == '\''
			|| (token->next->content)[0] == '\"')
		return (1);
	return (0);
}

int	concatenate(t_token **tokens)
{
	t_token	*temp;
	int		quote;

	temp = *tokens;
	while (temp != NULL && temp->next != NULL)
	{
		if (concat_redir(&temp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		temp = temp->next;
	}
	temp = *tokens;
	while (temp != NULL && temp->next != NULL)
	{
		quote = 0;
		if (temp->token_type == STRING && temp->next->token_type == STRING)
		{
			quote = quote_exist(temp);
			if (merge_nodes(&temp, &(temp->next), quote) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			temp = *tokens;
			continue ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
