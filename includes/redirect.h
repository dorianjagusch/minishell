/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:49:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/22 14:25:34 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"
# include <sys/wait.h>

# define READ 0
# define WRITE 1

int			redirect_exe(t_command *command, t_env *env);
size_t		count_commands(t_command *commands);
int			get_exe_path(t_env **env, t_command *command);
int			do_child(t_command *current, int *fds, int n_cmd, t_env *env);
void		close_fds(int *fds, int current, int n_cmd);
void		close_command_pipes(t_command *command);

#endif