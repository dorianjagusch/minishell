/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/26 10:21:30 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env, t_command *cmd, int out_fd)
{
	char	cur_dir[PATH_MAX];

	if (!env || !cmd)
		return (EXIT_FAILURE);
	if (getcwd(cur_dir, PATH_MAX))
	{
		ft_putendl_fd(cur_dir, out_fd);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
