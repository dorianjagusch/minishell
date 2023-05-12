/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:49:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/12 08:34:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

# define READ 0
# define WRITE 1

int			redirect_exe(t_command *command, t_env *env);
size_t		count_commands(t_command *commands);
int			get_exe_path(t_env **env, t_command *command);
void		do_child(t_command *head, int *fds, int current, char **env_arr);
void		close_fds(int *fds, int current, int n_cmd);

#endif