/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/19 11:15:21 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

BOOL	check_first_last(char *line)
{
	int		i;

	i = 0;
	if (line[0] == '|')
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	while (line[i])
	{
		i++;
	}
	if (line[i - 1] == '>' || line[i -1] == '<')
	{
		ft_printf("minishell: ");
		ft_printf("syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	if (line [i - 1] == '|')
	{
		ft_printf("minishell: ");
		ft_printf("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	return (FALSE);
}
