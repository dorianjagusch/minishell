/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/26 13:55:47 by djagusch         ###   ########.fr       */
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

typedef struct s_sytax_tree
{
	char	*command;
	char	**params;
	char	*infile;
	char	*outfile;
	int		in_fd[2];
	int		out_fd[2];
	t_syntax_tree	*next;
}			t_syntax_tree;

typedef struct s_builtin
{
	char *name;
	char 
}		t_builtin;

void		rl_replace_line(const char *text, int clear_undo);
void		init_env(char **envp, t_ev **env);
t_ev		*find_env(t_ev **env, char *variable);
t_ev		*new_env(char *key, char *value);

// BUILTINS
/* their prototypes need to be made equal
	We need to discuss the parser and abstract syntax tree, see comment abopve*/
int		find_built_in(t_ev **env, t_syntax_tree *cmd);
int		ft_echo(char **input);
void	ft_env(t_ev **env);
int		ft_pwd(t_ev *env);
int		ft_cd(char *path, t_ev **env);
int		ft_export(t_ev *env, char **args);
int		ft_unset(t_ev **env, char *variable);


#endif