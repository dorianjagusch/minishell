/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:55:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/05 09:32:23 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include "lexer.h"

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
	int					check;
	struct s_command	*next;
}						t_command;

t_command	*init_command(t_token *tokens);
void		free_command(t_command **commands);
void		print_parser(t_command **command);

#endif
