/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/28 12:58:01 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "lexer.h"
# include "ft_error.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BOOL int

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

void		rl_replace_line(const char *text, int clear_undo);
void		set_envp(char **envp, t_env **env);
int			init_lexer(char *line, t_token	**tokens);
int			retokenizer(t_token **tokens, t_env **env);
int			get_string(t_token **tokens, char *line, int quote);
void		replace_content(char *conent, int start, char **new, char *str);
int			get_comment(t_token **tokens, char *line);
t_token		*new_token(char *content, int token_type);
int			add_token(t_token **token, t_token *new);
void		free_tokens(t_token **tokens);

#endif