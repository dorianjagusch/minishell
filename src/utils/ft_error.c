/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:50:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/01 16:08:01 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <string.h>
#include "ft_error.h"

void	ft_error(int error, char *str)
{	
	ft_printf_fd(STDERR_FILENO, "minishell: ");
	if (error == NOCMMD)
		ft_printf_fd(STDERR_FILENO, "%s: command not found\n", str);
	else if (error == EACCES)
		ft_printf_fd(STDERR_FILENO, "%s: Permission denied %s\n", str);
	else
		ft_printf_fd(STDERR_FILENO, "%s: %s\n",
			str, strerror(error));
	if (error == ENOENT || error == NOCMMD | error == EACCES)
		g_info.exit_value = 1;
	else
		g_info.exit_value = error;
}
