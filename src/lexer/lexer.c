/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 10:25:25 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//protect mallocs
void	init_lexer(char *line, t_token	**token)
{
	int		i;

	token = (t_token *)ft_calloc(sizeof(t_token), 1);
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else if (line[i] == '\"')
			i += get_string(&token, &line[i], '\"');
		if (line[i] == '\'')
			i += get_string(&token, &line[i], '\'');
		if (ft_isprint(line[i]) && line[i] != '|' && line[i] != ';')
			i += get_command(&token, &line[i]);
		if (line[i] == '|')
			add_token(&token, new_token("|", PIPE));
		if (line[i] == '>')
			add_token(&token, new_token(">", GREATER_THAN));
		if (line[i] == '<')
			add_token(&token, new_token("<", LESS_THAN));
		if (line[i] == ';')
			add_token(&token, new_token(";", SEMICOLON));
	}
	//free_lexer(&lexer);
}
