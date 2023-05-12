/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/05/12 16:43:44 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	closing_quote(char *line)
{
	int		i;
	char	quote;
	int		close_found;

	i = -1;
	close_found = 0;
	quote = line[0];
	while (line[++i] && !close_found)
	{
		if (line[i] == quote)
			close_found = 1;
	}
	if (close_found == 0)
	{
		ft_printf("syntax error! Unclosed quotes.");
		return (-1);
	}
	return (i);
}

int	skip_quoted_text(char *line)
{
	int		i;
	char	quote;

	i = -1;
	quote = line[0];
	while (line[++i])
	{
		if (line[i] == quote)
			break ;
	}
	return (i);
}

int	skip_pipe(char *line)
{
	int	pipe;

	pipe = i;
	if (i == 0 || line[i + 1] == 0)
		return (-1);
	while (--i >= 0)
	{
		if (ft_isprint(line [i]) && line[i] != ' ')
			break ;
	}
	if (i == 0)
		return (-1);
	i = pipe - 1;
	while (line[++i])
	{
		if (ft_isprint(line [i]) && line[i] != ' ')
		{
			if (line[i] != '>' || line[i] != '<' || line[i] != '|')
				return (-1);
			else
				break ;
		}
	}
	if (line[i + 1] == 0)
		return (-1);
	return (1);
}

int	skip_redir(char *line)
{
	int		redir_pos;
	char	redir;

	redir = line[i];
	if (line[i + 1] == 0)
		return (-1);
	if (line[i + 1] == redir)
		i++;
	redir_pos = i;
	while (--i >= 0)
	{
		if (ft_isprint(line [i]) && line[i] != ' ')
		{
			if (line[i] != '>' || line[i] != '<' || line[i] != '|')
				return (-1);
			else
				break ;
		}
	}
	if (i == 0)
		return (-1);
	i = redir_pos -1;
	while (line[++i])
	{
		if (ft_isprint(line [i]) && line[i] != ' ')
		{
			if (line[i] != '>' || line[i] != '<' || line[i] != '|')
				return (-1);
			else
				break ;
		}
	}
	if (line[i + 1] == 0)
		return (-1);
	return (1);
}
