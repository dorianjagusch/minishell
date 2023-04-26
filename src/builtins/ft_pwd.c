/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:19 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/26 13:28:34 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_ev *env)
{
	char	cur_dir[PATH_MAX];

	if (getcwd(cur_dir, PATH_MAX))
	{
		ft_putendl(cur_dir);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
