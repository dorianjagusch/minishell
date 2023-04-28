/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/28 16:30:26 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_white(t_token **tokens, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
	}
	if (add_token(&tokens, new_token(" ", SPACE)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (i);
}

int	get_string(t_token **tokens, char *line, int quote)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != quote)
		i++;
	str = ft_calloc(sizeof(char) * (i + 2), 1);
	if (!str)
		retun (EXIT_FAILURE);
	ft_strlcpy(str, line, i + 2);
	if (add_token(tokens, new_token(str, STRING)) == EXIT_FAILURE)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	free(str);
	return (i + 1);
}

int	get_comment(t_token **tokens, char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] == '-')
		i++;
	while (line[i] && line[i] != '\t' && line[i] != ' ' && line[i] != '|'
		&& line[i] != '\"' && line[i] != '\'')
		i++;
	str = ft_calloc(sizeof(char) * (i + 1), 1);
	if (!str)
		retun (EXIT_FAILURE);
	ft_strlcpy(str, line, i + 1);
	if (add_token(tokens, new_token(str, COMMAND)) == EXIT_FAILURE)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	free(str);
	return (i - 1);
}

t_token	*new_token(char *content, int token_type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		return (NULL);
	}
	new->token_type = token_type;
	new->next = NULL;
	return (new);
}

int	add_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = *token;
	if (new == NULL)
		return (EXIT_FAILURE);
	if (*token == NULL)
		*token = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (EXIT_SUCCESS);
}
