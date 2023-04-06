/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:24:34 by djagusch          #+#    #+#             */
/*   Updated: 2022/11/15 13:24:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_c(unsigned int n, int c)
{
	char	*hex;
	int		length;

	if (n == 0)
		return (ft_putchar_c('0'));
	hex = ft_dec_hexstr(n);
	if (!hex)
		return (return_null());
	if ('a' <= c && c <= 'z')
		ft_strlower(hex);
	length = ft_putstr_c(hex);
	free(hex);
	return (length);
}
