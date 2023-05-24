/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/24 12:40:58 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	add_line(t_heredoc **hrdc, t_heredoc *new_hrdc)
{
	t_heredoc	*tmp;

	tmp = *hrdc;
	if (new_hrdc == NULL)
		return (EXIT_FAILURE);
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
		return (NULL);
	new->line = ft_strdup(str);
	new->next = NULL;
	return (new);
}

static	void	write_to_pipe(t_heredoc *hrdc, int fd, int is_quote)
{
	while (hrdc)
	{
		write(fd, (hrdc->line), ft_strlen(hrdc->line));
		write(fd, "\n", 1);
		hrdc = hrdc->next;
	}
	free_hrdc(hrdc);
}

int	here_doc(char	*delim, int is_quote)
{
	int			fd[2];
	char		*line;
	t_heredoc	*heredoc;
	//block signals
	if (pipe(fd) < 0)
		ft_error(EPIPE, "");
	heredoc = NULL;
	while (1)
	{
		line = readline("> ");
		if (ft_strlen(line) > 0)
		{
			if (ft_strncmp(delim, line, ft_strlen(line)) != 0
				&& add_line(&heredoc, new_doc(line)) == EXIT_FAILURE)
			{
				free_hrdc(heredoc);
				free(line);
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
			else
			{
				free(line);
				break ;
			}
			free(line);
		}
	}
	write_to_pipe(heredoc, fd[1], is_quote);
	return (fd[0]);
}
