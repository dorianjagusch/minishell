/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/08 14:03:29 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_white(t_token **tokens, char *line, int *flag)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
			break ;
	}
	if (add_token(tokens, new_token(" ", SPACE), flag) == EXIT_FAILURE
		|| *flag == -1)
		*flag = -1;
	//ft_printf("return value from skip white%d\n", i);
	return (i);
}

static int	get_string(t_token **tokens, char *line, int quote, int *flag)
{
	char	*str;
	int		i;

	i = 1;
	while (line[i] != quote)
		i++;
	str = ft_calloc(sizeof(char) * (i + 2), 1);
	if (!str)
		*flag = -1;
	ft_strlcpy(str, line, i + 2);
	if (add_token(tokens, new_token(str, STRING), flag) == EXIT_FAILURE
		|| *flag == -1)
	{
		if (str)
			free(str);
		*flag = -1;
	}
	free(str);
	//ft_printf("return value from string%d\n", i + 2);
	return (i + 2);
}

static int	get_text(t_token **tokens, char *line, int *flag)
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
		*flag = -1;
	ft_strlcpy(str, line, i + 1);
	if (add_token(tokens, new_token(str, STRING), flag) == EXIT_FAILURE
		|| *flag == -1)
	{
		if (str)
			free(str);
		*flag = -1;
	}
	free(str);
	//ft_printf("return value from get text%d\n", i);
	return (i);
}

int	init_lexer(char *line, t_token	**tokens)
{
	int		i;
	int		indicator;

	i = 0;
	while (line[i])
	{
		//ft_printf ("line : %s\n",&line[i]);
		indicator = i;
		if (line[i] == ' ' || line[i] == '\t')
			i += skip_white(tokens, &line[i], &indicator);
		else if (line[i] == '\"')
			i += get_string(tokens, &line[i], '\"', &indicator);
		else if (line[i] == '\'')
			i += get_string(tokens, &line[i], '\'', &indicator);
		else if (line[i] == '|')
			i += add_token(tokens, new_token("|", PIPE), &indicator);
		else if (line[i] == '>')
			i += add_token(tokens, new_token(">", GREATER_THAN), &indicator);
		else if (line[i] == '<')
			i += add_token(tokens, new_token("<", LESS_THAN), &indicator);
		else if (ft_isprint(line[i]) && line[i] != '|' && line[i] != ' ')
			i += get_text(tokens, &line[i], &indicator);
		if (indicator == -1)
			return (EXIT_FAILURE);
		//ft_printf("i :%d indicator:%d\n",i,indicator);
	}
	return (EXIT_SUCCESS);
}
