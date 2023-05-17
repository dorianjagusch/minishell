/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:50:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/15 13:03:12 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <string.h>
#include "ft_error.h"

void	ft_error(int error, char *str)
{	
	if (error == 0)
		exit(1);
	ft_printf_fd(STDERR_FILENO, "MiniShell&>: ");
	if (error == NOFILE)
		ft_printf_fd(STDERR_FILENO, "no such file or directory: %s\n",
			str);
	else if (error == NOACCESS)
		ft_printf_fd(STDERR_FILENO, "%s: %s\n", strerror(EACCES), str);
	else
	{
		if (error == EACCES)
			ft_printf_fd(STDERR_FILENO, "%s: %s\n",
				str, strerror(error));
		else if (error == NOCMMD)
			ft_printf_fd(STDERR_FILENO, "command not found: %s\n", str);
		exit(error);
	}
}
