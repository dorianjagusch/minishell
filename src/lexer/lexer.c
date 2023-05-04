/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/04 13:21:19 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_white(t_token **tokens, char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
	}
	if (add_token(tokens, new_token(" ", SPACE)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (i);
}

static int	get_string(t_token **tokens, char *line, int quote)
{
	char	*str;
	int		i;

	i = 0;
	while (line[i] != quote)
		i++;
	str = ft_calloc(sizeof(char) * (i + 2), 1);
	if (!str)
		return (EXIT_FAILURE);
	ft_strlcpy(str, line, i + 2);
	if (add_token(tokens, new_token(str, STRING)) == EXIT_FAILURE)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	free(str);
	return (i + 1);
}

static int	get_text(t_token **tokens, char *line)
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
		return (EXIT_FAILURE);
	ft_strlcpy(str, line, i + 1);
	if (add_token(tokens, new_token(str, STRING)) == EXIT_FAILURE)
	{
		free(str);
		return (EXIT_FAILURE);
	}
	free(str);
	return (i - 1);
}

int	init_lexer(char *line, t_token	**tokens)
{
	int		i;
	int		indicator;

	i = -1;
	while (line[++i])
	{
		indicator = i;
		if (line[i] == ' ' || line[i] == '\t')
			i += skip_white(tokens, &line[i]);
		if (line[i] == '\"')
			i += get_string(tokens, &line[i], '\"');
		if (line[i] == '\'')
			i += get_string(tokens, &line[i], '\'');
		if (line[i] == '|')
			i += add_token(tokens, new_token("|", PIPE));
		if (line[i] == '>')
			i += add_token(tokens, new_token(">", GREATER_THAN));
		if (line[i] == '<')
			i += add_token(tokens, new_token("<", LESS_THAN));
		if (ft_isprint(line[i]) && line[i] != '|')
			i += get_text(tokens, &line[i]);
		if (indicator > i)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
