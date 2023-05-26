/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/25 10:19:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	add_line(t_heredoc **hrdc, t_heredoc *new_hrdc)
{
	t_heredoc	*tmp;

	tmp = *hrdc;
	if (new_hrdc == NULL)
	{
		free_hrdc(hrdc);
		return (EXIT_FAILURE);
	}
	if (*hrdc == NULL)
		*hrdc = new_hrdc;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_hrdc;
	}
	return (EXIT_SUCCESS);
}

static	t_heredoc	*new_doc(char *str)
{
	t_heredoc	*new;

	new = malloc(sizeof(t_heredoc));
	if (!new)
	{
		free(str);
		return (NULL);
	}
	new->line = ft_strdup(str);
	new->next = NULL;
	return (new);
}

//expand if is not quote
static	void	write_to_pipe(t_heredoc *hrdc, int fd, int is_quote)
{
	is_quote = 0;
	while (hrdc)
	{
		write(fd, (hrdc->line), ft_strlen(hrdc->line));
		write(fd, "\n", 1);
		hrdc = hrdc->next;
	}
	free_hrdc(&hrdc);
}

static	int	process_line(t_heredoc	*heredoc, char *line, int *fd, char	*delim)
{
	if (ft_strncmp(delim, line, ft_strlen(line)) != 0)
	{
		if (add_line(&heredoc, new_doc(line)) == EXIT_FAILURE)
		{
			close(fd[0]);
			close(fd[1]);
			return (-1);
		}
	}
	else
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

//signal break
int	here_doc(char	*delim, int is_quote)
{
	int			fd[2];
	char		*line;
	t_heredoc	*heredoc;
	int			ret;

	if (pipe(fd) < 0)
		ft_error(EPIPE, "");
	heredoc = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) > 0)
		{
			ret = process_line(heredoc, line, fd, delim);
			if (ret == 0)
				break ;
			if (ret == -1)
				return (-1);
		}
	}
	write_to_pipe(heredoc, fd[1], is_quote);
	return (fd[0]);
}
