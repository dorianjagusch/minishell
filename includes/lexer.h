/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/04 13:18:55 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

# define BOOL int

typedef struct s_token
{
	int				token_type;
	int				isquote;
	char			*content;
	struct s_token	*next;
}					t_token;

enum e_token_type
{
	STRING,
	COMMAND,
	GREATER_THAN,
	GREATER_GREATER,
	LESS_THAN,
	LESS_LESS,
	PIPE,
	SPACE
};

t_token		*new_token(char *content, int token_type);
int			add_token(t_token **token, t_token *new);
int			concatenate(t_token **tokens);

#endif