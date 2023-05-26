/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/05/26 13:47:02 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "syntax.h"
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

typedef struct s_heredoc
{
	char				*line;
	struct s_heredoc	*next;
}						t_heredoc;

typedef struct s_info
{
	t_token		*tokens;
	t_command	*commands;
	char		*line;
	int			**fds;
	int			*pids;
	int			exit_value;
	t_heredoc	*heredoc;
	t_env		*env;
}		t_info;

t_info		g_info;

void		rl_replace_line(const char *text, int clear_undo);
void		init_env(char *envp[], t_env **env);
int			init_lexer(char *line, t_token	**tokens);
int			retokenize(t_token **tokens, t_env **env);
t_env		*find_env(t_env **env, char *variable, int predecessor);
t_env		*new_env(char *key, char *value);
void		add_env(t_env **env, t_env *new);
t_env		*copy_env(t_env **env);
char		**ft_env_to_array(t_env *env);

char		*find_value(t_env **env, char *key);

//SYNTAX_CHECK AND TOKENIZE
int			init_lexer(char *line, t_token	**tokens);
int			retokenize(t_token **tokens, t_env **env);
BOOL		syntax_check(char *line);


//free
void		ft_clear_everything(t_info g_info);
void		free_tokens(t_token **tokens);
void		free_env(t_env **env);

//here_doc
int			here_doc(char	*delim, int is_quote);
void		free_hrdc(t_heredoc **hrdc);

//signal
void		init_signal(void);
void		heredoc_signal(void);

// BUILTINS
int			is_builtin(t_command *cmd);
BOOL		exec_builtin(t_env **env, t_command *cmd);
int			ft_echo(t_env **env, t_command *cmd);
int			ft_env(t_env **env, t_command *cmd);
int			ft_pwd(t_env **env, t_command *cmd);
int			ft_cd(t_env **env, t_command *cmd);
int			ft_export(t_env **env, t_command *cmd);
int			print_export(t_env **env, t_command *cmd);
int			ft_unset(t_env **env, t_command *cmd);
void		print_token(t_token *token);

void		ft_clear(t_command **command, int **pids, int **fds);
#endif