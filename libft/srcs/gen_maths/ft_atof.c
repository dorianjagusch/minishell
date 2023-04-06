/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:26:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/01/26 13:45:04 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_digits(const char *str, size_t i)
{
	int		j;
	double	result;

	j = -1;
	result = 0;
	while ('0' <= str[i] && str[i] <= '9' && str[i] && str[i] != '.')
		result = (result * 10) + (str[i++] - '0');
	if (str[i++] == '.')
	{
		while ('0' <= str[i] && str[i] <= '9' && str[i])
			result += ((str[i++] - '0') * ft_powerf(10, j--));
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		i;
	int		sign;
	double	result;

	sign = 1;
	i = 0;
	while (str[i] && (str[i] == '\t' || str[i] == ' ' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\n' || str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	result = get_digits(str, i);
	result *= sign;
	return (result);
}
