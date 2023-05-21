/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:29:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/17 12:27:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_array(char **str, int fd)
{
	int	i;

	i = -1;
	if (!str || fd < 0)
		return ;
	while (str[++i])
		ft_putendl_fd(str[i], fd);
}

void	ft_print_intarr(int *arr, int size, int fd)
{
	int	i;

	i = -1;
	if (!arr || !size || fd < 0)
		return ;
	while (++i < size)
		ft_putnbr_fd(arr[i], fd);
}
