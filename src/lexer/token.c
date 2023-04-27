/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/26 13:56:38 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//strings include srounding single or double quotos
int	get_string(t_token **token, char *line, int quote)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != quote)
		i++;
	str = ft_calloc(sizeof(char) * (i + 2), 1);
	ft_strlcpy(str, line, i + 2);
	add_token(token, new_token(str, STRING));
	free(str);
	return (i + 1);
}

int	get_comment(t_token **token, char *line)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] == '-')
		i++;
	while (line[i] && line[i] != '\t' && line[i] != ' ' && line[i] != '|'
		&& line[i] != 34  && line[i] != 44)
		i++;
	str = ft_calloc(sizeof(char) * (i + 1), 1);
	ft_strlcpy(str, line, i + 1);
	add_token(token, new_token(str, COMMAND));
	free(str);
	return (i - 1);
}

t_token	*new_token(char *content, int token_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content); //protect strdup fail
	new->token_type = token_type;
	new->next = NULL;
	return (new);
}

void	add_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	tmp = *token;
	if (*token == NULL)
		*token = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
