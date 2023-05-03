/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/03 14:08:34 by asarikha         ###   ########.fr       */
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

	temp = ft_strjoin(token->content, next_token->content);
	if (temp)
	{
		free(token->content);
		token->content = temp;
		token->next = next_token->next;
		free(next_token->next->content);
		free(next_token);
		return (EXIT_SUCCESS);
	}
	else
		return (EXIT_FAILURE);
}
