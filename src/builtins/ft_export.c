/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 14:53:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/04/26 17:42:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_env(char *arg)
{
	size_t	i;
	size_t	len;
	size_t	eq_pos;

	if (!ft_isalpha(arg[0]) || arg[0] != '_')
		return (-1);
	i = 0;
	len = ft_strlen(arg);
	eq_pos = 0;
	while (arg[eq_pos] && arg[eq_pos] != '=')
		eq_pos++;
	if (i < eq_pos && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	if (i != len - 1)
		return (i);
	return (-1);
}

replace_env()
{
	
}

int	ft_export(t_ev *env, char **args)
{
	size_t	i;
	size_t	eq_pos;
	char	*key;
	char	*value;

	if (!args)
		return (1);
	i = 0;
	eq_pos = invalid_env(args[i]);
	if (eq_pos < 0)
		return (1);
	key = ft_calloc(eq_pos + 1, sizeof(char));
	if (!key)
		return (1);
	key = ft_strlcpy(key, args[i], eq_pos++);
	value = ft_strdup(args[i] + eq_pos);
	if (!value)
		return (1);
	if (find)
	// add arg to list
}