/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:29:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/03 21:57:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(char **str, int fd)
{
	size_t	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_putendl_fd(str[i], fd);
}
