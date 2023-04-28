/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/28 15:51:41 by asarikha         ###   ########.fr       */
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
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BOOL int

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_builtin
{
	char	*name;
	int		(*builtin)(t_ev **, t_command *);
}		t_builtin;

void		rl_replace_line(const char *text, int clear_undo);
void		set_envp(char **envp,t_env **env);
int			init_lexer(char *line,t_token	**tokens);
int			retokenizer(t_token **tokens, t_env **env);
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