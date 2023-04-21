/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/20 14:41:57 by asarikha         ###   ########.fr       */
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
# include "ft_error.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BOOL int

typedef struct s_ev
{
	char		*key;
	char		*value;
	struct s_ev	*next;
}				t_ev;

typedef struct s_lexer
{
	enum
	{
		STRING,
		COMMAND,
		greater_than,
		GREATER_GREATER,
		LESS_THAN,
		LESS_LESS,
		SEMICOLON,
		PIPE,
	}		e_token_type;
	char				*content;
	struct s_lexer		*next;
}	t_lexer;

void		rl_replace_line(const char *text, int clear_undo);
void		set_envp(char **envp, t_ev **env);

#endif