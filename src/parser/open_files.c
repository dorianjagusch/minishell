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
	int		file_type;

	file_type = 0;
	if (token_type == LESS_LESS || token_type == LESS_THAN)
		file = command->infile;
	else
	{
		file_type++;
		file = command->outfile;
	}
	if (file && access(file, F_OK))
		ft_error(NOFILE, file);
	else if (file && command->fds[file_type] < 0 && access(file, F_OK) == 0)
		ft_error(NOACCESS, file);
}

t_token	*get_fds(t_command *command, t_token *token)
{
	if (token->token_type == LESS_THAN)
		command->fds[0] = open(command->infile, O_RDONLY);
	else if (token->token_type == LESS_LESS)
		command->fds[0] = -1;
	else if (token->token_type == GREATER_THAN)
	{
		command->fds[1] = open(command->outfile,
				O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else
	{
		command->fds[1] = open(command->outfile,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	check_file(command, token->token_type);
	return (token);
}
 // write for outfiles