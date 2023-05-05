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

static void	check_files(t_command *command)
{
	if (command->infile)
	{
		if (access(command->infile, F_OK))
			ft_error(NOFILE, command->infile);
		else if (command->fds[0] < 0 && access(command->infile, F_OK) == 0)
			ft_error(NOACCESS, command->infile);
	}
	if (command->outfile)
	{
		if (access(command->outfile, F_OK))
			ft_error(NOFILE, command->outfile);
		else if (command->fds[1] < 0
			&& access(command->outfile, F_OK) == 0)
			ft_error(NOACCESS, command->outfile);
	}
	if (command->fds[0] < 0 || command->fds[1] < 0)
		ft_error(0, "");
}

/*IDEA: Take the list of command and open the respective file into their fd
arrays, if they have an infile and or outfile name */

void	get_fds(t_command *command, size_t n_cmds)
{
	int	i;

	i = -1;
	while (command)
	{
		set_up_pipe(command);
		if (command->infile)
		{
			close(command->fds[0]);
			if (command->id == 1)
				close(command->fds[]);
			command->fds[0] = open(command->infile, O_RDONLY | O_CLOEXEC);
		}
		else if (command->id == 1)
			command->fds[0] = STDIN_FILENO;
		if (command->outfile)
		{
			command->fds[1] = open(command->outfile,
					O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
		}
		else if (command->id == n_cmds)
			command->fds[1] = STDOUT_FILENO;
		check_files(command);
		command == command->next;
	}
}
