/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:07:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/05/10 12:23:50 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env **env, char *key, int predecessor)
{
	t_env	*tmp;

	if (!env || !*env || !key || !(*key))
		return (NULL);
	tmp = *env;
	if (!predecessor)
	{
		while (tmp)
		{
			if (ft_strcmp(key, tmp->key) == 0)
				break ;
			tmp = tmp->next;
		}
	}
	else
	{
		while (ft_strcmp(key, tmp->key) != 0 && tmp && tmp->next)
		{
			if (ft_strcmp(key, tmp->next->key) == 0)
				break ;
			tmp = tmp->next;
		}
	}
	return (tmp);
}

char	*find_value(t_env **env, char *key)
{
	t_env	*tmp;

	if (!env || !*env || !key || !(key[0]))
		return (NULL);
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		return (tmp->value);
	return (NULL);
}