/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/08 15:17:14 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_command *head, int *(fds[2]), int cur, int n_cmd)
{
	size_t	pipe;

	pipe = 0;
	while (pipe <= n_cmd)
	{
		if (pipe != cur && pipe != n_cmd)
			close(fds[pipe][0]);
		if (pipe != cur + 1 && pipe != 0)
			close(fds[pipe][1]);
		pipe++;
	}
}

