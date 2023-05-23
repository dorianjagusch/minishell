/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/23 14:42:03 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//malloc needs to be protected.
static	void	add_line(t_heredoc **hrdc, t_heredoc *new_hrdc)
{
	t_heredoc	*tmp;

	tmp = *hrdc;
	if (*hrdc == NULL)
		*hrdc = new_hrdc;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_hrdc;
	}
}

static	t_heredoc	*new_doc(char *str)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
		return (NULL);
	new->line = ft_strdup(str);
	new->next = NULL;
	return (new);
}

static	void	write_to_pipe(t_heredoc *hrdc, int fd)
{
	while (hrdc)
	{
		write(fd, (hrdc->line), ft_strlen(hrdc->line));
		hrdc = hrdc->next;
	}
	free(heredoc);
}

int	here_doc(char *infile, char	*delim;)
{
	int			fd[2];
	char		*line;
	t_heredoc	*heredoc;

	if (pipe(fd) < 0)
		ft_error();
	heredoc = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) > 0)
		{
			if (ft_strncmp(delim, line, ft_strlen(line)) != 0)
				add_line(&heredoc, new_doc(line));
			else
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	write_to_pipe(heredoc, fd)
	return (fd);
}
