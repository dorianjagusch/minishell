/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/29 13:17:25 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env, t_command *cmd)
{
	char	cur_dir[PATH_MAX];

	if (getcwd(cur_dir, PATH_MAX))
	{
		ft_putendl_fd(cur_dir, cmd->out_fd[1]);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
