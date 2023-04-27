/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 12:30:58 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_lexer(char *line, t_token	**tokens)
{
	int		i;
	int		indicator;

	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		indicator = i;
		else if (line[i] == '\"')
			i += get_string(&tokens, &line[i], '\"');
		else if (line[i] == '\'')
			i += get_string(&tokens, &line[i], '\'');
		else if (line[i] == '|')
			i += add_token(&tokens, new_token("|", PIPE));
		else if (line[i] == '>')
			i += add_token(&tokens, new_token(">", GREATER_THAN));
		else if (line[i] == '<')
			i += add_token(&tokens, new_token("<", LESS_THAN));
		else if (ft_isprint(line[i]) && line[i] != '|' && line[i] != ';')
			i += get_command(&tokens, &line[i]);
		if (indicator > i)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
