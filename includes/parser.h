/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:55:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/04 12:32:08 by djagusch         ###   ########.fr       */
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
	int					in_fd[2];
	int					out_fd[2];
	int					check;
	struct s_command	*next;
}						t_command;

t_command	*init_command(t_token *tokens);
void		free_command(t_command **commands);

#endif
