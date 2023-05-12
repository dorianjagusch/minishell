/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/10 12:06:26 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "lexer.h"
# include "ft_error.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TRUE 1
# define FALSE 0


typedef struct s_env
{
	char			*key;
	char			*value;
	BOOL			eq;
	struct s_env	*next;
}				t_env;

typedef struct s_builtin
{
	char	*name;
	int		(*builtin)(t_env **, t_command *);
}		t_builtin;

void		rl_replace_line(const char *text, int clear_undo);
void		init_env(char **envp, t_env **env);
int			init_lexer(char *line, t_token	**tokens);
int			retokenize(t_token **tokens, t_env **env);
void		init_env(char **envp, t_env **env);
t_env		*find_env(t_env **env, char *variable, int predecessor);
t_env		*new_env(char *key, char *value);
void		add_env(t_env **env, t_env *new);
void		free_tokens(t_token **tokens);
t_env		*copy_env(t_env **env);
void		free_env(t_env **env);
char		*find_value(t_env **env, char *key);

// BUILTINS
int			is_built_in(t_env **env, t_command *cmd);
int			ft_echo(t_env **env, t_command *cmd);
int			ft_env(t_env **env, t_command *cmd);
int			ft_pwd(t_env **env, t_command *cmd);
int			ft_cd(t_env **env, t_command *cmd);
int			ft_export(t_env **env, t_command *cmd);
int			print_export(t_env **env, t_command *cmd);
int			ft_unset(t_env **env, t_command *cmd);
void		print_token(t_token *token);

#endif