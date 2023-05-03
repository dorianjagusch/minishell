/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/03 17:32:50 by djagusch         ###   ########.fr       */
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

typedef struct s_env
{
	char			*key;
	char			*value;
	BOOL			eq;
	struct s_env	*next;
}				t_env;

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

int			retokenize(t_token **tokens, t_env **env);
int			get_string(t_token **tokens, char *line, int quote);
char		*replace_content(char *content, int start, char *new, char *str);
int			get_command(t_token **tokens, char *line);
t_token		*new_token(char *content, int token_type);
int			add_token(t_token **token, t_token *new);
void		free_tokens(t_token **tokens);

#endif