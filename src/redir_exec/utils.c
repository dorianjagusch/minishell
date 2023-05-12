/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:37:54 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/11 16:19:16 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(int *fds, int cur, int n_cmd)
{
	int	pipe;

	pipe = 0;
	while (pipe <= n_cmd)
	{
		if (pipe != cur && pipe != n_cmd)
			close(fds[cur + 0]);
		if (pipe != cur + 1 && pipe != 0)
			close(fds[cur + 1]);
		pipe++;
	}
}

