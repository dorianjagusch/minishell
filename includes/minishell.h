/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 12:41:17 by djagusch         ###   ########.fr       */
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
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BOOL int

typedef struct s_ev
{
	char		*key;
	char		*value;
	struct s_ev	*next;
}				t_ev;

enum e_token_type
{
	STRING,
	COMMAND,
	GREATER_THAN,
	GREATER_GREATER,
	LESS_THAN,
	LESS_LESS,
	PIPE
};

typedef struct s_token
{
	int				token_type;
	char			*content;
	struct s_token	*next;
}					t_token;

typedef struct s_builtin
{
	char	*name;
	int		(*builtin)(t_ev **, t_command *);
}		t_builtin;

void		rl_replace_line(const char *text, int clear_undo);
void		init_env(char **envp, t_ev **env);
t_ev		*find_env(t_ev **env, char *variable);
t_ev		*new_env(char *key, char *value);
void		add_env(t_ev **env, t_ev *new);

// BUILTINS
/* their prototypes need to be made equal
	We need to discuss the parser and abstract syntax tree, see comment abopve*/
int			find_built_in(t_ev **env, t_command *cmd);
int			ft_echo(t_ev **env, t_command *cmd);
int			ft_env(t_ev **env, t_command *cmd);
int			ft_pwd(t_ev **env, t_command *cmd);
int			ft_cd(t_ev **env, t_command *cmd);
int			ft_export(t_ev **env, t_command *cmd);
int			ft_unset(t_ev **env, t_command *cmd);


#endif