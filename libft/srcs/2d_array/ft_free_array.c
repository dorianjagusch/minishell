/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:20:20 by djagusch          #+#    #+#             */
/*   Updated: 2023/03/11 15:14:26 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_array(char ***array, size_t index)
{
	int	i;

	i = 0;
	while (i < (int) index)
	{
		ft_free((*array)[i]);
		(*array)[i++] = NULL;
	}
	ft_free(*array);
	array = NULL;
	return (NULL);
}
