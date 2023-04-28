/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/28 14:10:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env **env, t_command *cmd)
{
	char	cur_dir[PATH_MAX];

	if (getcwd(cur_dir, PATH_MAX))
	{
		ft_putendl(cur_dir);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
