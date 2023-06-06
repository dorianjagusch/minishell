/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/06/06 11:17:50 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_synt_error(char c)
{
	ft_putstr_fd("\033[1m\e[31mGayAsHell\x1b[m: syntax error near ", 2);
	if (c == '|')
		ft_putstr_fd("unexpected token `|', sis 💅\n", 2);
	else if (c == '\n')
		ft_putstr_fd("unexpected token `newline', sis 💅\n", 2);
	else if (c == '<' || c == '>')
	{
		ft_putstr_fd("unexpected token `", 2);
		write(2, &c, 1);
		write(2, &c, 1);
		ft_putstr_fd("', sis 💅\n", 2);
	}
}

BOOL	check_first(char *line)
{
	if (line[0] == '|')
	{
		print_synt_error(line[0]);
		return (TRUE);
	}
	return (FALSE);
}

BOOL	check_last(char *line)
{
	int		last;

	last = ft_strlen(line) - 1;
	if (line[last] == '>' || line[last] == '<'
		|| line [last] == '|')
	{
		if ((line[last] == '>' || line[last] == '<')
			&& line[last] == line[last - 1])
		{
			ft_putstr_fd("unexpected token `", 2);
			write(2, &line[last - 1], 1);
			write(2, &line[last - 1], 1);
			ft_putstr_fd("', sis 💅\n", 2);
		}
		else
			print_synt_error('\n');
		return (TRUE);
	}
	return (FALSE);
}
