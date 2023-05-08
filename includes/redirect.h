/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:49:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/08 15:23:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

# define READ 0
# define WRITE 1

int			redirect_exe(t_command *command, t_env *env);
size_t		count_commands(t_command *commands);
char		*get_exe_path(t_env **env, t_command *command);
void		close_fds(t_command *head, int *(fds[2]), int cur, int n_cmd);

#endif