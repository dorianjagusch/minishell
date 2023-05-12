/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/12 16:47:11 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


BOOL	quotes_close(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = closing_quote(&line[i]);
		else
			i++;
		if (i == -1)
			return (FALSE);
	}
	return (TRUE);
}

//pipes can not be in the begining or the end and pipes should have some text in
//between themselves or else they are empty pipes

BOOL	empty_pipe(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = skip_quoted_text(&line[i]);
		if ((line[i] == '|'))
			i = skip_pipe(line, i);
		else
			i++;
		if (i == -1)
		{
			ft_printf("syntax error! Empty pipe.");
			return (FALSE);
		}
	}
	return (TRUE);
}

//redirections can not be with no text after them

BOOL	empty_redir(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = skip_quoted_text(&line[i]);
		if ((line[i] == '>' || line[i] == '<'))
			i = skip_redir(line, i);
		else
			i++;
		if (i == -1)
		{
			ft_printf("syntax error! Empty redirection.");
			return (FALSE);

		}
	}
	return (TRUE);
}

BOOL	syntax_check(char *line)
{
	if (!quotes_close(line))
		return (FALSE);
	if (empty_pipe(line))
		return (FALSE);
	if (empty_redir(line))
		return (FALSE);
	return (TRUE);
}
