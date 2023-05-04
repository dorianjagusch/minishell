/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/04 12:25:13 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_content(char *content, int start, char *new, char *str)
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

static	char	*expand_content(t_token **token, int start, t_env **env)
{
	int		end;
	int		i;
	char	*str;
	char	*new;

	end = start;
	i = 0;
	while (ft_isalnum((*token)->content[end]) && (*token)->content[end])
	{
		str[i] = (*token)->content[end];
		end++;
	}
	str = find_env(env, str, 0);
	if (str)
	{
		i = ft_strlen((*token)->content) + 1;
		new = ft_calloc(i, 1);
		if (!new)
			return (NULL);
		new = replace_content((*token)->content, start, new, str);
		free((*token)->content);
		(*token)->content = new;
	}
	return ((*token)->content);
}

static	int	expander(t_token **tokens, t_env **env)
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
					tmp->content = expand_content(&tmp, i, env);
					if (tmp->content == NULL)
						return (EXIT_FAILURE);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

int	retokenizer(t_token **tokens, t_env **env)
{
	if (!expander(tokens, env))
		return (EXIT_FAILURE);
	if (!concatenate(tokens))
		return (EXIT_FAILURE);
	if (re_label(tokens))
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
