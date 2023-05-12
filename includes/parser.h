/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:55:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/11 11:24:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include <sys/types.h>

typedef struct s_command
{
	char				*command;
	char				**params;
	char				n_params;
	int					in_redirect;
	int					out_redirect;
	char				*infile;
	char				*outfile;
	int					fds[2];
	size_t				id;
	struct s_command	*next;
}						t_command;

t_command	*init_command(t_token *tokens);
t_command	*set_command(t_command *head, size_t id);
void		free_command(t_command **commands);
void		print_parser(t_command *command);
t_token		*get_fds(t_command *command, t_token *token);
BOOL		ft_isredir(t_token *token);

#endif
