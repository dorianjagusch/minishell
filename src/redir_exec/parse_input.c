/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:06:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/02/10 13:28:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_error.h"

static void	check_files(t_command *commands)
{
	if (commands->infile)
	{
		if (access(commands->infile, F_OK))
			ft_error(NOFILE, commands->infile);
		else if (commands->fds[0] < 0 && access(commands->infile, F_OK) == 0)
			ft_error(NOACCESS, commands->infile);
	}
	if (commands->outfile)
	{
		if (access(commands->outfile, F_OK))
			ft_error(NOFILE, commands->outfile);
		else if (commands->fds[1] < 0
			&& access(commands->outfile, F_OK) == 0)
			ft_error(NOACCESS, commands->outfile);
	}
	if (commands->fds[0] < 0 || commands->fds[1] < 0)
		ft_error(0, "");
}

/*IDEA: Take the list of commands and open the respective file into their fd
arrays, if they have an infile and or outfile name */

void	get_fds(t_command *commands)
{
	int	i;

	i = -1;
	if (commands->infile)
		commands->fds[0] = open(commands->infile, O_RDONLY | O_CLOEXEC);
	else
		commands->fds[0] = STDIN_FILENO;
	if (commands->outfile)
	{
		commands->fds[1] = open(commands->outfile,
				O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	}
	else
		commands->fds[0] = STDOUT_FILENO;
	check_files(commands);
}

