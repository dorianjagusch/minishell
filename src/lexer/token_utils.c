/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/03 15:22:50 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_content(char *content, int start, char *new, char *str)
{
	int		i;
	int		end;
	int		j;
	int		len;

	i = -1;
	j = -1;
	end = ft_strlen(str);
	len = -1;
	while (++i < start)
		new[i] = content[++len];
	while (++i < end)
		new[i] = str[++j];
	end = ft_strlen(content);
	while (++i < end)
		new[i] = content[++len];
	new[i] = 0;
	return (new);
}

BOOL	can_concat(t_token **token)
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

int	concat_redir(t_token *token)
{
	t_token	*temp;

	temp = token;
	if ((temp->token_type == GREATER_THAN && temp->next->token_type
			== GREATER_THAN) || (temp->token_type == LESS_THAN
			&& temp->next->token_type == LESS_THAN))
	{
		free(temp->content);
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

int	merge_nodes(t_token *token, t_token *next_token, int quote)
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
