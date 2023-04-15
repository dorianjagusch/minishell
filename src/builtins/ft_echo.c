/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:11:43 by asarikha          #+#    #+#             */
/*   Updated: 2023/04/15 15:13:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Assuming that the string is already parsed and the variables are expanded.
// Execve will give us the COMMAND as the first ebntry in the array.
// That's why i starts at 1.

int	ft_echo(char **input)
{
	BOOL	n_flag;
	int		i;

	n_flag = 0;
	i = 1;
	if (input[i] && ft_strcmp(input[i], "-n"))
		n_flag = 1;
	while (input[i] && ft_strcmp(input[i], "-n"))
		i++;
	while (input[i])
	{
		ft_putstr(input);
		if (input[i + 1] && input [i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
