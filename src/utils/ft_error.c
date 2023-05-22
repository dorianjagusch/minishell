/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:50:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/22 14:37:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <string.h>
#include "ft_error.h"

void	ft_error(int error, char *str)
{	
	if (error == 0)
	{
		ft_printf_fd(STDERR_FILENO, "%s\n", str);
		exit(1);
	}
	ft_printf_fd(STDERR_FILENO, "MiniShell&>: ");
	if (error == NOFILE)
		ft_printf_fd(STDERR_FILENO, "no such file or directory: %s\n",
			str);
	else
	{
		if (error == EACCES)
			ft_printf_fd(STDERR_FILENO, "%s: %s\n",
				strerror(error), str);
		else if (error == NOCMMD)
			ft_printf_fd(STDERR_FILENO, "command not found: %s\n", str);
		exit(error);
	}
}
