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

static void	check_file(t_command *command, int token_type)
{
	char	*file;

	if (token_type == GREATER_GREATER || token_type == GREATER_THAN)
		file = command->infile;
	else
		file = command->outfile;
	if (access(file, F_OK))
		ft_error(NOFILE, file);
	else if (command->fds[0] < 0 && access(file, F_OK) == 0) //fd is not correct here
		ft_error(NOACCESS, file);
}

t_token	*get_fds(t_command *command, t_token *token)
{
	if (command->infile
		&& (token->token_type == GREATER_GREATER
			|| token->token_type == GREATER_THAN))
		command->fds[0] = open(command->infile, O_RDONLY | O_CLOEXEC);
	else
		command->fds[0] = -1;
	if (command->outfile)
	{
		command->fds[1] = open(command->outfile,
				O_RDWR | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
	}
	else
		command->fds[1] = -1;
	check_file(command, token->token_type);
	return (token->next);
}
