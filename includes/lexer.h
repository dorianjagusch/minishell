/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/28 12:57:50 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_token
{
	enum
	{
		STRING,
		COMMAND,
		GREATER_THAN,
		GREATER_GREATER,
		LESS_THAN,
		LESS_LESS,
		PIPE,
	}		e_token_type;
	char				*content;
	struct s_token		*next;
}	t_token;

int			get_string(t_token **tokens, char *line, int quote);
void		replace_content(char *conent, int start, char **new, char *str);
int			get_comment(t_token **tokens, char *line);
t_token		*new_token(char *content, int token_type);
int			add_token(t_token **token, t_token *new);
void		free_tokens(t_token **tokens);

#endif