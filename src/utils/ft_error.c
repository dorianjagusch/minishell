/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:50:57 by djagusch          #+#    #+#             */
/*   Updated: 2023/06/09 15:10:13 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <string.h>
#include "ft_error.h"

void	ft_error(int error, char *str)
{	
	ft_printf_fd(STDERR_FILENO, "\033[1m\e[31mGayAsHell\x1b[m: ");
	if (error == NOCMMD)
		ft_printf_fd(STDERR_FILENO, "%s: command not found", str);
	else if (error == EACCES)
		ft_printf_fd(STDERR_FILENO, "%s: Permission denied", str);
	else if (error == ARGERR)
		ft_printf_fd(2, "export: `%s': not a valid identifier", str);
	else
		ft_printf_fd(STDERR_FILENO, "%s: %s",
			str, strerror(error));
	ft_printf_fd(STDERR_FILENO, ", sis 💅\n");
	if (error == ENOENT || error == NOCMMD || error == EACCES
		|| error == ARGERR)
		g_info.exit_value = 1;
	else
		g_info.exit_value = error;
}
