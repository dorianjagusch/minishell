/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/31 13:13:17 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

BOOL	check_first_last(char *line)
{
	int		i;

	i = 0;
	if (line[0] == '|')
	{
		ft_putstr_fd("GayAsHell: syntax error near unexpected token `|'\n", 2);
		return (TRUE);
	}
	while (line[i])
	{
		i++;
	}
	if (line[i - 1] == '>' || line[i -1] == '<')
	{
		ft_putstr_fd("GayAsHell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return (TRUE);
	}
	if (line [i - 1] == '|')
	{
		ft_putstr_fd("GayAsHell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (TRUE);
	}
	return (FALSE);
}
