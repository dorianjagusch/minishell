/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/04 14:03:06 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_content(char *content, int start, char *new, char *str)
{
	int		i;
	int		old_len;
	int		end;
	int		j;
	int		len;

	i = -1;
	j = -1;
	end = ft_strlen(str);
	len = -1;
	old_len = ft_strlen(content) + 1;
	new = ft_calloc(old_len, 1);
	if (!new)
		return (EXIT_FAILURE);
	while (++i < start)
		new[i] = content[++len];
	while (++i < end)
		new[i] = str[++j];
	end = ft_strlen(content);
	while (++i < end)
		new[i] = content[++len];
	free(content);
	content = new;
	return (EXIT_SUCCESS);
}

static int	re_label(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;

	if (temp->token_type == GREATER_THAN || temp->token_type == LESS_THAN
		|| temp->token_type == LESS_LESS
		|| temp->token_type == GREATER_GREATER)
		temp->next->next->token_type = COMMAND;
	else
		temp->token_type = COMMAND;
	while (temp != NULL)
	{
		if (temp->token_type == PIPE)
		{
			temp = temp->next;
			if (temp->token_type == LESS_LESS || temp->token_type == LESS_THAN
				|| temp->token_type == GREATER_THAN
				|| temp->token_type == GREATER_GREATER)
			temp->next->next->token_type = COMMAND;
			else
				temp->token_type = COMMAND;
		}
		temp = temp->next;
	}
	return (EXIT_SUCCESS);
}

static	int	expand_content(t_token **token, int start, t_env **env)
{
	int		end;
	char	*str;
	char	*new;
	char	*value;

	end = start;
	new = NULL;
	while ((ft_isalnum((*token)->content[end])
			|| (*token)->content[end] == '_') && (*token)->content[end])
		end++;
	str = ft_substr((*token)->content, start, end - start);
	if (!str)
		return (EXIT_FAILURE);
	value = find_env(env, str, 0)->value;
	if (value)
	{
		if (replace_content((*token)->content, start, new, value))
		{
			free(str);
			return (EXIT_SUCCESS);
		}
	}
	free(str);
	return (EXIT_FAILURE);
}

static	int	expand(t_token **tokens, t_env **env)
{
	t_token	*tmp;
	int		i;

	tmp = *tokens;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (tmp->content[i] == '$')
			{
				if (tmp->content[0] != '\'')
				{
					if (!expand_content(&tmp, i, env))
						return (EXIT_FAILURE);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	retokenize(t_token **tokens, t_env **env)
{
	if (!expand(tokens, env))
		return (EXIT_FAILURE);
	if (!concatenate(tokens))
		return (EXIT_FAILURE);
	if (re_label(tokens))
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
