/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/11 17:03:27 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	concat_redir(t_token **token)
{
	t_token *temp;
	
	//ft_printf("in concat redir\n");
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
		temp = (*token)->next;
		(*token)->next = (*token)->next->next;
		free(temp->content);
		free(temp);
	}
	//ft_printf("exiting concat redir with success\n");
	return (EXIT_SUCCESS);
}

static	int	bzero_quote(t_token *token, t_token *next_token, char *temp
, char *next_temp)
{
	if ((token->content)[0] == '\'' || (token->content)[0] == '\"')
	{
		temp = ft_substr(token->content, 1, ft_strlen(token->content) - 2);
		if (temp)
		{
			free(token->content);
			token->content = temp;
		}
		else
			return (EXIT_FAILURE);
	}
	ft_printf("content : %s\n", token->content);
	ft_printf("next content : %s\n", token->next->content);
	if ((next_token->content)[0] == '\'' || (next_token->content)[0] == '\"')
	{
		next_temp = ft_substr(next_token->content, 1,
				ft_strlen(next_token->content) - 2);
		if (next_temp)
		{
			free(next_token->content);
			next_token->content = next_temp;
		}
		else
			return (EXIT_FAILURE);
	}
	ft_printf("content : %s\n", token->content);
	ft_printf("next content : %s\n", token->next->content);
	return (EXIT_SUCCESS);
}

static int	quote_check(t_token *token)
{
	if ((token->content)[0] == '\'' || (token->content)[0] == '\"'
			|| token->isquote == 1 || (token->next->content)[0] == '\''
			|| (token->next->content)[0] == '\"')
		return (1);
	return (0);
}

static int	merge_nodes(t_token **token, t_token **next_token, int quote)
{
	char	*temp;
	char	*tmp;
	char	*next_tmp;
	t_token	*ptr;

	tmp = NULL;
	next_tmp = NULL;
	ft_printf("in merge nodes\n");
	if (quote_check(*token))
		if (bzero_quote((*token), (*next_token), tmp, next_tmp) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	temp = ft_strjoin((*token)->content, (*next_token)->content);
	if (temp)
	{
		ft_printf("temp : %s\n", temp);
		free((*token)->content);
		(*token)->content = temp;
		ft_printf("content : %s\n", (*token)->content);
		ptr = (*next_token);
		(*token)->next = (*token)->next->next;
		(*token)->isquote = quote;
		free(ptr->content);
		free(ptr);
		ft_printf("here\n");
		if ((*token)->next)
			ft_printf("next content : %s\n", (*token)->next->content);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
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
	ft_printf("after concat redir\n");
	print_token(*tokens);
	while (temp != NULL && temp->next != NULL)
	{
		quote = 0;
		if (temp->token_type == STRING && temp->next->token_type == STRING)
		{
			quote = quote_check(temp);
			if (merge_nodes(&temp, &(temp->next), quote) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			temp = *tokens;
			print_token(*tokens);
			continue ;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}
