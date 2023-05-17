/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:31:11 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/17 14:29:39 by asarikha         ###   ########.fr       */
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
	int		ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			ret = closing_quote(&line[i]);
			if (ret == -1)
				return (FALSE);
			i += ret;
		}
		else
			i++;
	}
	return (TRUE);
}

static BOOL	empty_pipe(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quoted_text(&line[i]);
		if ((line[i] == '|' && line[i + 1]))
			i += skip_pipe(line, i);
		else
			i++;
		if (i == -1)
		{
			ft_printf("minishell: ");
			ft_printf("syntax error near unexpected token `newline'\n");
			return (TRUE);
		}
	}
	if (line [i - 1] == '|')
	{
		ft_printf("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	return (FALSE);
}

static BOOL	empty_redir(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i += skip_quoted_text(&line[i]);
		if ((line[i] == '>' || line[i] == '<') && line[i + 1])
			i += skip_redir(&line[i]);
		else
			i++;
		if (i == -1)
		{
			ft_printf("minishell: syntax error! Empty unexpected `newline'\n");
			return (TRUE);
		}
	}
	if (line[i - 1] == '>' || line[i -1] == '<')
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		return (TRUE);
	}
	return (FALSE);
}

BOOL	syntax_check(char *line)
{
	if (line[0] == '|')
	{
		ft_printf("minishell: syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	if (!quotes_close(line))
		return (FALSE);
	if (empty_pipe(line))
		return (FALSE);
	if (empty_redir(line))
		return (FALSE);
	return (TRUE);
}
