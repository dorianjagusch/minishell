/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/15 13:31:01 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int *fds, int cur, int n_cmd)
{
	int	pipe;

	pipe = 0;
	while (pipe <= n_cmd)
	{
		if (pipe != cur)
			close(fds[cur + 0]);
		if (pipe != cur + 1)
			close(fds[cur + 1]);
		pipe++;
	}
}

