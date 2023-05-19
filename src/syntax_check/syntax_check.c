/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/19 11:12:40 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	closing_quote(char *line)
{
	int		i;
	char	quote;
	int		close_found;

	i = 0;
	close_found = 0;
	quote = line[0];
	while (line[++i] && !close_found)
	{
		if (line[i] == quote)
			close_found = 1;
	}
	if (close_found == 0)
	{
		ft_printf("minishell: syntax error! Unclosed quotes.\n");
		return (-1);
	}
	return (i);
}

static BOOL	quotes_close(char *line)
{
	int		i;
	int		result;

	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			result = closing_quote(&line[i]);
			if (result == -1)
				return (FALSE);
			i += result;
		}
		else
			i++;
	}
	return (TRUE);
}

static BOOL	empty_pipe(char *line)
{
	int		i;
	int		result;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quoted_text(&line[i]);
		if ((line[i] == '|' && line[i + 1]))
		{
			result = skip_pipe(line, i);
			if (result == -1)
			{
				ft_printf("minishell: ");
				ft_printf("syntax error near unexpected token `newline'\n");
				return (TRUE);
			}
			i += result;
		}
		else
			i++;
	}
	return (FALSE);
}

static BOOL	empty_redir(char *line)
{
	int		i;
	int		result;

	result = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quoted_text(&line[i]);
		if ((line[i] == '>' || line[i] == '<') && line[i + 1])
		{
			result = skip_redir(&line[i]);
			if (result == -1)
			{
				ft_printf("minishell: ");
				ft_printf("syntax error! Empty unexpected `newline'\n");
				return (TRUE);
			}
			i += result;
		}
		else
			i++;
	}
	return (FALSE);
}

BOOL	syntax_check(char *line)
{
	if (check_first_last(line))
		return (FALSE);
	if (!quotes_close(line))
		return (FALSE);
	if (empty_pipe(line))
		return (FALSE);
	if (empty_redir(line))
		return (FALSE);
	return (TRUE);
}
