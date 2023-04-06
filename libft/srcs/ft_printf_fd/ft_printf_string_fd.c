/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:22:19 by djagusch          #+#    #+#             */
/*   Updated: 2022/11/15 13:22:21 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_c2(char *s, int fd)
{
	int	len;

	if (!s)
		return (return_null2(fd));
	len = ft_strlen(s);
	return (write(fd, s, len));
}
