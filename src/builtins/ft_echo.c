/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/27 11:38:02 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Assuming that the string is already parsed and the variables are expanded.
// Execve will give us the COMMAND as the first entry in the array.
// That's why i starts at 1.

int	ft_echo(t_ev **env, t_command *cmd)
{
	BOOL	n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (cmd->params[i] && ft_strcmp(cmd->params[i], "-n"))
		n_flag = 1;
	while (cmd->params[i] && ft_strcmp(cmd->params[i], "-n"))
		i++;
	while (cmd->params[i])
	{
		ft_putstr(cmd->params);
		if (cmd->params[i + 1] && cmd->params[i][0])
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
